/* zftap1_tn: TN / NE oracle for the zf1 port (fork B).  Derived from zftap1.c.
 *
 * Usage: zftap1_tn.exe <tests.txt> <out.txt> [log]
 *   Speaks one warm-up sentence with David to create the engine objects (captures the CTextNormalizer and
 *   CNEDetector instances through vtable hooks), then runs each test line directly against the engine:
 *     N<TAB>category<TAB>text   CTextNormalizer::Normalize (vt+0x18 = 0x1800c3e50) -> output word list
 *     E<TAB>text                CNEDetector::FindNext loop (vt+0x18 = 0x180061910), like 1800c6888 does:
 *                               hit -> advance past the entity, miss -> stop
 *     S<TAB>text                Speak the text normally (logs NE/TN hook calls, "sayas" contexts etc.)
 *   Output (UTF-8):  one "Q ..." line echoing the query, then result lines.
 */
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#include <windows.h>
#include <sapi.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define ENGINE_DLL L"C:\\Windows\\System32\\Speech_OneCore\\Engines\\TTS\\MSTTSEngine_OneCore.dll"
#define TOKID L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices\\Tokens\\MSTTS_V110_enUS_DavidM"
#define RVA_LOG   0x029190
#define RVA_VT_TN 0x1763b0   /* CTextNormalizer: +0x18 Normalize(this, text, category, outList) */
#define RVA_VT_NE 0x16f0c8   /* CNEDetector:     +0x18 FindNext(this, text, len, category, &pre, &len, CTTSString*, u16*) */

static BYTE *g_base;
static FILE *g_out;
static int g_log, g_inspeak;
static void *g_tn, *g_ne, *g_strvt;

static void putw8(const wchar_t *s, int n)
{
    char buf[8];
    if (!s) { fputs("(null)", g_out); return; }
    for (int i = 0; n < 0 ? s[i] : i < n; i++) {
        unsigned c = s[i];
        if (c < 0x20 || c == '\\' || c == '"' || c == 0x7f) { fprintf(g_out, "\\x%02x", c); continue; }
        int k = 0;
        if (c < 0x80) buf[k++] = (char)c;
        else if (c < 0x800) { buf[k++] = (char)(0xC0 | (c >> 6)); buf[k++] = (char)(0x80 | (c & 63)); }
        else { buf[k++] = (char)(0xE0 | (c >> 12)); buf[k++] = (char)(0x80 | ((c >> 6) & 63)); buf[k++] = (char)(0x80 | (c & 63)); }
        fwrite(buf, 1, k, g_out);
    }
}

static void my_log(int level, const wchar_t *fmt, ...)
{
    wchar_t buf[8192];
    va_list ap;
    if (!g_log) return;
    va_start(ap, fmt);
    _vsnwprintf(buf, 8191, fmt, ap);
    va_end(ap);
    buf[8191] = 0;
    fprintf(g_out, "LOG%d ", level); putw8(buf, -1); fputc('\n', g_out);
}

static void write_jmp(BYTE *at, void *to)
{
    DWORD old;
    VirtualProtect(at, 14, PAGE_EXECUTE_READWRITE, &old);
    at[0] = 0xFF; at[1] = 0x25; *(DWORD *)(at + 2) = 0;
    *(void **)(at + 6) = to;
    VirtualProtect(at, 14, old, &old);
    FlushInstructionCache(GetCurrentProcess(), at, 14);
}

/* engine list: {head link*, tail, count, pool, free, grow}; link = {next, prev, item} */
typedef struct EList { void *head, *tail; unsigned __int64 count; void *pool, *freel; unsigned __int64 grow; void *pad[4]; } EList;

typedef HRESULT (*NormFn)(void *, const wchar_t *, const wchar_t *, void *);
typedef HRESULT (*FindFn)(void *, const wchar_t *, unsigned, const wchar_t *, unsigned *, unsigned *, void *, unsigned short *);
static NormFn g_orig_norm;
static FindFn g_orig_find;

static void print_list(EList *l)
{
    int first = 1;
    for (BYTE *lk = l->head; lk; lk = *(BYTE **)lk) {
        fprintf(g_out, first ? "\"" : " \"");
        first = 0;
        putw8(*(const wchar_t **)(lk + 0x10), -1);
        fputc('"', g_out);
    }
}

static HRESULT my_norm(void *self, const wchar_t *text, const wchar_t *cat, void *out)
{
    HRESULT hr;
    g_tn = self;
    hr = g_orig_norm(self, text, cat, out);
    if (g_inspeak) {
        fprintf(g_out, "TN hr=%08lx cat=\"", (unsigned long)hr); putw8(cat, -1); fprintf(g_out, "\" in=\"");
        putw8(text, -1); fprintf(g_out, "\" out=");
        print_list((EList *)out);
        fputc('\n', g_out);
    }
    return hr;
}

typedef struct TStr { void *vt; wchar_t *buf; unsigned __int64 a, b; } TStr;

static HRESULT my_find(void *self, const wchar_t *text, unsigned len, const wchar_t *cat, unsigned *pre, unsigned *elen,
                       void *catstr, unsigned short *attr)
{
    HRESULT hr;
    g_ne = self;
    if (!g_strvt && catstr) g_strvt = *(void **)catstr;
    hr = g_orig_find(self, text, len, cat, pre, elen, catstr, attr);
    if (g_inspeak) {
        fprintf(g_out, "NE hr=%lx cat=\"", (unsigned long)hr); putw8(cat ? cat : L"", -1);
        fprintf(g_out, "\" in=\""); putw8(text, (int)len); fprintf(g_out, "\"");
        if (hr == 0) {
            fprintf(g_out, " pre=%u len=%u type=\"", pre ? *pre : 0, elen ? *elen : 0);
            putw8(catstr ? ((TStr *)catstr)->buf : NULL, -1);
            fprintf(g_out, "\" attr=%u", attr ? *attr : 0);
        }
        fputc('\n', g_out);
    }
    return hr;
}

static void patch_slot(DWORD rva_vt, int slot, void *fn, void **orig)
{
    DWORD old;
    void **p = (void **)(g_base + rva_vt + slot * 8);
    *orig = *p;
    VirtualProtect(p, 8, PAGE_READWRITE, &old);
    *p = fn;
    VirtualProtect(p, 8, old, &old);
}

static wchar_t *u8tow(const char *b, int n)
{
    int wn = MultiByteToWideChar(CP_UTF8, 0, b, n, NULL, 0);
    wchar_t *w = malloc((wn + 1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, b, n, w, wn);
    w[wn] = 0;
    return w;
}

static void do_norm(const wchar_t *cat, const wchar_t *text)
{
    EList l;
    HRESULT hr;
    memset(&l, 0, sizeof l);
    l.grow = 10;
    __try {
        hr = g_orig_norm(g_tn, text, cat, &l);
        fprintf(g_out, "R hr=%08lx out=", (unsigned long)hr);
        print_list(&l);
        fputc('\n', g_out);
    } __except (EXCEPTION_EXECUTE_HANDLER) { fprintf(g_out, "R EXC\n"); }
}

/* ---- P mode: network best path tree (network vt+0x10) ---- */
typedef HRESULT (*MkLatFn)(void *, const wchar_t *, int, void **, void *, int);
typedef HRESULT (*BestFn)(void *, void *, unsigned short, unsigned, const wchar_t *, void **, unsigned short *);
static void dump_path(BYTE *n, int depth)
{
    if (!n) { fprintf(g_out, "%*s(null)\n", depth * 2, ""); return; }
    int type = *(int *)(n + 8);
    unsigned short cnt = *(unsigned short *)(n + 0x28);
    fprintf(g_out, "%*sT%d rule=%u glue=%d cost=%u span=%u-%u i30=%d i78=%d", depth * 2, "", type, *(unsigned short *)(n + 0x34),
            *(int *)(n + 0x18), *(unsigned short *)(n + 0x2a), *(unsigned short *)(n + 0x72), *(unsigned short *)(n + 0x74),
            *(int *)(n + 0x30), *(int *)(n + 0x78));
    if (*(wchar_t **)(n + 0x80)) { fprintf(g_out, " cat=\""); putw8(*(wchar_t **)(n + 0x80), -1); fputc('"', g_out); }
    BYTE *attrs = *(BYTE **)(n + 0x38);
    if (attrs && *(unsigned short *)(attrs + 8)) {
        fprintf(g_out, " attrs=");
        for (int i = 0; i < *(unsigned short *)(attrs + 8); i++) {
            BYTE *a = (*(BYTE ***)attrs)[i];
            fprintf(g_out, "%s%x/%x/%x", i ? "," : "", *(unsigned *)a, *(unsigned *)(a + 4), *(unsigned *)(a + 8));
        }
    }
    if (type == 0) {
        fprintf(g_out, " text=\"");
        if (*(wchar_t **)(n + 0x20)) putw8(*(wchar_t **)(n + 0x20), cnt);
        fprintf(g_out, "\"\n");
    } else {
        fprintf(g_out, " n=%u\n", cnt);
        for (int i = 0; i < cnt; i++) dump_path((*(BYTE ***)(n + 0x10))[i], depth + 1);
    }
}
static void do_path(const wchar_t *cat, const wchar_t *text, unsigned mode)
{
    __try {
        void *net = *(void **)((BYTE *)g_tn + 8);
        void *lat = NULL, *path = NULL;
        unsigned short len = 0;
        HRESULT hr = ((MkLatFn)(g_base + 0x138e18))(net, text, 0, &lat, *(void **)((BYTE *)g_tn + 0x10), mode == 1 ? 3 : 0);
        fprintf(g_out, "R lat hr=%08lx", (unsigned long)hr);
        if (hr < 0 || !lat) { fputc('\n', g_out); return; }
        hr = ((BestFn)((*(void ***)net)[2]))(net, lat, 0, mode, (cat && *cat) ? cat : NULL, &path, &len);
        fprintf(g_out, " best hr=%08lx len=%u\n", (unsigned long)hr, len);
        if (path) dump_path((BYTE *)path, 1);
    } __except (EXCEPTION_EXECUTE_HANDLER) { fprintf(g_out, "R EXC\n"); }
}

static void do_find(const wchar_t *cat, const wchar_t *text)
{
    unsigned n = (unsigned)wcslen(text), pos = 0;
    __try {
        while (pos < n) {
            TStr cs = { g_strvt, 0, 0, 0 };
            unsigned pre = 0, len = 0;
            unsigned short attr = 0;
            HRESULT hr = g_orig_find(g_ne, text + pos, n - pos, cat, &pre, &len, &cs, &attr);
            fprintf(g_out, "R hr=%lx", (unsigned long)hr);
            if (hr != 0) { fputc('\n', g_out); break; }
            fprintf(g_out, " at=%u len=%u type=\"", pos + pre, len);
            putw8(cs.buf, -1);
            fprintf(g_out, "\" attr=%u \"", attr);
            putw8(text + pos + pre, (int)len);
            fprintf(g_out, "\"\n");
            if (!len) break;
            pos += pre + len;
        }
    } __except (EXCEPTION_EXECUTE_HANDLER) { fprintf(g_out, "R EXC\n"); }
}

/* ---- M mode: the NE FST matcher alone (CFstMatcher = ne+0x28): FUN_180075900 creates a matcher on the text,
 * FUN_180067e78 = next match, FUN_1800d5ba8 = offset, FUN_1800d5ac8 = length, FUN_18006755c = output string ---- */
typedef HRESULT (*FstApplyFn)(void *, const wchar_t *, void **);
typedef char (*FstNextFn)(void *, void *);
typedef void (*FstI64Fn)(void *, __int64 *);
typedef void (*FstStrFn)(void *, void *);
typedef void (*StrCtorFn)(void *);
typedef const char *(*StrCstrFn)(void *);
typedef void (*FstFreeFn)(void *, void *);
static void do_match(const wchar_t *text)
{
    void *m = NULL;
    __try {
        void *fstm = *(void **)((BYTE *)g_ne + 0x28);
        HRESULT hr = ((FstApplyFn)(g_base + 0x75900))(fstm, text, &m);
        fprintf(g_out, "R apply hr=%08lx\n", (unsigned long)hr);
        if (hr < 0 || !m) return;
        for (int k = 0; k < 1000; k++) {
            __int64 off = 0, len = 0;
            unsigned __int64 s[8];
            char r = ((FstNextFn)(g_base + 0x67e78))(m, m);
            if (!r) break;
            memset(s, 0, sizeof s);
            ((StrCtorFn)(g_base + 0x4d824))(s);
            ((FstI64Fn)(g_base + 0xd5ba8))(m, &off);
            ((FstI64Fn)(g_base + 0xd5ac8))(m, &len);
            ((FstStrFn)(g_base + 0x6755c))(m, s);
            fprintf(g_out, "M off=%lld len=%lld out=\"%s\"\n", off, len, ((StrCstrFn)(g_base + 0x23160))(s));
        }
    } __except (EXCEPTION_EXECUTE_HANDLER) { fprintf(g_out, "R EXC %08lx\n", (unsigned long)GetExceptionCode()); }
}

int wmain(int argc, wchar_t **argv)
{
    if (argc < 3) { fprintf(stderr, "usage: zftap1_tn tests.txt out.txt [log]\n"); return 1; }
    if (argc > 3 && !_wcsicmp(argv[3], L"log")) g_log = 1;
    g_out = _wfopen(argv[2], L"wb");
    FILE *cf = _wfopen(argv[1], L"rb");
    if (!g_out || !cf) { fprintf(stderr, "cannot open files\n"); return 1; }
    fseek(cf, 0, SEEK_END); long cn = ftell(cf); fseek(cf, 0, SEEK_SET);
    char *cb = malloc(cn + 1); fread(cb, 1, cn, cf); cb[cn] = 0; fclose(cf);

    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    g_base = (BYTE *)LoadLibraryW(ENGINE_DLL);
    if (!g_base) { fprintf(stderr, "cannot load engine\n"); return 1; }
    if (memcmp(g_base + RVA_LOG, "\x48\x8b\xc4\x48\x89\x50\x10", 7) == 0) write_jmp(g_base + RVA_LOG, (void *)my_log);
    patch_slot(RVA_VT_TN, 3, (void *)my_norm, (void **)&g_orig_norm);
    patch_slot(RVA_VT_NE, 3, (void *)my_find, (void **)&g_orig_find);

    ISpObjectToken *tok = NULL; ISpVoice *v = NULL; ISpStream *st = NULL; IStream *mem = NULL;
    HRESULT hr = CoCreateInstance(&CLSID_SpObjectToken, NULL, CLSCTX_ALL, &IID_ISpObjectToken, (void **)&tok);
    if (SUCCEEDED(hr)) hr = ISpObjectToken_SetId(tok, NULL, TOKID, FALSE);
    if (SUCCEEDED(hr)) hr = CoCreateInstance(&CLSID_SpVoice, NULL, CLSCTX_ALL, &IID_ISpVoice, (void **)&v);
    if (SUCCEEDED(hr)) hr = ISpVoice_SetVoice(v, tok);
    if (FAILED(hr)) { fprintf(stderr, "voice setup failed %08lx\n", hr); return 1; }
    WAVEFORMATEX wf = { WAVE_FORMAT_PCM, 1, 16000, 32000, 2, 16, 0 };
    CreateStreamOnHGlobal(NULL, TRUE, &mem);
    CoCreateInstance(&CLSID_SpStream, NULL, CLSCTX_ALL, &IID_ISpStream, (void **)&st);
    hr = ISpStream_SetBaseStream(st, mem, &SPDFID_WaveFormatEx, &wf);
    if (SUCCEEDED(hr)) hr = ISpVoice_SetOutput(v, (IUnknown *)st, TRUE);
    ISpVoice_Speak(v, L"On 12/25/2013 I paid $5.", SPF_DEFAULT, NULL);
    if (!g_tn || !g_ne || !g_strvt) { fprintf(stderr, "objects not captured %p %p %p\n", g_tn, g_ne, g_strvt); return 1; }
    {
        BYTE *lx = *(BYTE **)((BYTE *)g_tn + 0x10), *nl = *(BYTE **)((BYTE *)g_ne + 0x10);
        fprintf(g_out, "INFO tn=%p tn.lex=%p vt=%llx posid=%u | ne.lex=%p vt=%llx ne+18=%u ne+20 vt=%llx ne+28=%p\n",
                g_tn, lx, lx ? (unsigned long long)(*(BYTE **)lx - g_base) : 0, *(unsigned short *)((BYTE *)g_tn + 0x18),
                nl, nl ? (unsigned long long)(*(BYTE **)nl - g_base) : 0, *(unsigned short *)((BYTE *)g_ne + 0x18),
                *(BYTE **)((BYTE *)g_ne + 0x20) ? (unsigned long long)(**(BYTE ***)((BYTE *)g_ne + 0x20) - g_base) : 0,
                *(void **)((BYTE *)g_ne + 0x28));
        void *o20 = *(void **)((BYTE *)g_ne + 0x20);
        if (o20) fprintf(g_out, "INFO ne+20 vt+0x38() = %d\n", ((int (*)(void *))((*(void ***)o20)[7]))(o20));
    }

    char *p = cb;
    if ((BYTE)p[0] == 0xEF && (BYTE)p[1] == 0xBB && (BYTE)p[2] == 0xBF) p += 3;
    while (*p) {
        char *e = p;
        while (*e && *e != '\n') e++;
        int n = (int)(e - p);
        if (n && p[n - 1] == '\r') n--;
        if (n > 2 && p[1] == '\t' && (p[0] == 'N' || p[0] == 'E' || p[0] == 'S' || p[0] == 'C' || p[0] == 'P' || p[0] == 'F' || p[0] == 'R' || p[0] == 'M')) {
            wchar_t *w = u8tow(p, n);
            fprintf(g_out, "Q "); putw8(w, -1); fputc('\n', g_out);
            if (w[0] == 'N') {
                wchar_t *t = wcschr(w + 2, L'\t');
                if (t) { *t = 0; do_norm(w + 2, t + 1); }
            } else if (w[0] == 'P') {   /* P<TAB>category<TAB>text : best path tree, mode 2 */
                wchar_t *t = wcschr(w + 2, L'	');
                if (t) { *t = 0; do_path(w + 2, t + 1, 2); }
            } else if (w[0] == 'R') {   /* R<TAB>text : best path tree in NE mode (mode 1, no category, tokenizer 3) */
                do_path(NULL, w + 2, 1);
            } else if (w[0] == 'E') {
                do_find(NULL, w + 2);
            } else if (w[0] == 'M') {   /* M<TAB>text : NE FST matcher matches */
                do_match(w + 2);
            } else if (w[0] == 'F') {   /* F<TAB>text : FindNext loop with the CFstMatcher (ne+0x28) disabled */
                void *save = *(void **)((BYTE *)g_ne + 0x28);
                *(void **)((BYTE *)g_ne + 0x28) = NULL;
                do_find(NULL, w + 2);
                *(void **)((BYTE *)g_ne + 0x28) = save;
            } else if (w[0] == 'C') {   /* C<TAB>category<TAB>text : FindNext with a category */
                wchar_t *t = wcschr(w + 2, L'\t');
                if (t) { *t = 0; do_find(w + 2, t + 1); }
            } else {
                g_inspeak = 1;
                ISpVoice_Speak(v, w + 2, SPF_DEFAULT, NULL);
                g_inspeak = 0;
            }
            fflush(g_out);
            free(w);
        }
        p = *e ? e + 1 : e;
    }
    fclose(g_out);
    return 0;
}
