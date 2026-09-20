/* zftap1: text-frontend (first half) ground-truth dumper for the OneCore en-US engine.
 * Copy of ziratap.c extended with a CTTSUtterance tree dump at the end of CTextProcessor (handler 0x40000,
 * phase "after") = the zf1 stage boundary.  See notes/fe1.md.
 *
 * Usage:  zftap1.exe <voice> <corpus.txt> <dump.txt> [full] [log] [hooks]
 *   corpus: UTF-8, one utterance per line (each line = one ISpVoice::Speak(SPF_DEFAULT), so a line starting with
 *           '<' is parsed as SAPI XML by SAPI).  Empty lines and lines starting with "##" are skipped.
 *   full  : run the whole pipeline (default: skip every handler after the text processor -> fast)
 *   log   : also print the engine trace log lines
 *   hooks : log intermediate stages (TN Normalize in/out etc.)
 * Dump format (UTF-8), per corpus line:
 *   L <lineno>\t<text>
 *   F act=.. ...               SPVTEXTFRAG list as given by SAPI
 *   S off=.. len=.. type=.. emo=.. a0=.. a4=.. n=<words> lists=<counts of sentence lists>
 *   W <fields>                 one per CTTSWord in sentence+0x110 (see dump_word)
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
#define TOKROOT L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices\\Tokens\\"

#define RVA_LOG        0x029190
#define RVA_SPEAK      0x08b210
#define RVA_VT_TTSENG  0x175210
#define OFF_ENGINE_FROM_ITTS 0x68
#define OFF_STAGE_OBS  0x578

static BYTE *g_base;
static FILE *g_out;
static CRITICAL_SECTION g_lock;
static int g_full, g_log, g_hooks;

static void putw8(const wchar_t *s, int n)
{
    /* write wide string as UTF-8, escaping control chars, backslash and quote */
    char buf[16];
    if (!s) { fputs("(null)", g_out); return; }
    for (int i = 0; n < 0 ? s[i] : i < n; i++) {
        unsigned c = s[i];
        if (c >= 0xD800 && c < 0xDC00 && (n < 0 ? s[i + 1] : i + 1 < n)) {
            unsigned d = s[i + 1];
            if (d >= 0xDC00 && d < 0xE000) { c = 0x10000 + ((c - 0xD800) << 10) + (d - 0xDC00); i++; }
        }
        if (c < 0x20 || c == '\\' || c == '"' || c == 0x7f) { fprintf(g_out, "\\x%02x", c); continue; }
        int k = 0;
        if (c < 0x80) buf[k++] = (char)c;
        else if (c < 0x800) { buf[k++] = (char)(0xC0 | (c >> 6)); buf[k++] = (char)(0x80 | (c & 63)); }
        else if (c < 0x10000) { buf[k++] = (char)(0xE0 | (c >> 12)); buf[k++] = (char)(0x80 | ((c >> 6) & 63)); buf[k++] = (char)(0x80 | (c & 63)); }
        else { buf[k++] = (char)(0xF0 | (c >> 18)); buf[k++] = (char)(0x80 | ((c >> 12) & 63)); buf[k++] = (char)(0x80 | ((c >> 6) & 63)); buf[k++] = (char)(0x80 | (c & 63)); }
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
    EnterCriticalSection(&g_lock);
    fprintf(g_out, "LOG%d ", level); putw8(buf, -1); fputc('\n', g_out);
    LeaveCriticalSection(&g_lock);
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

/* ---------------- utterance dump ---------------- */
typedef unsigned __int64 u64;
#define P(p, off) (*(BYTE **)((BYTE *)(p) + (off)))
#define I32(p, off) (*(int *)((BYTE *)(p) + (off)))
#define U16(p, off) (*(unsigned short *)((BYTE *)(p) + (off)))
static void *g_strvt;   /* CTTSString vftable (learned from word+0x98) */

static const wchar_t *tstr(BYTE *obj, int off) { return *(const wchar_t **)(obj + off + 8); }

static void pstr(const char *name, const wchar_t *s)
{
    fprintf(g_out, " %s=\"", name);
    if (s) putw8(s, -1);
    fputc('"', g_out);
}

static void dump_word(BYTE *w)
{
    static const int ints[] = { 0x84, 0x88, 0x180, 0x210, 0x214, 0x228, 0x22c, 0x230, 0x234, 0x238, 0x23c, 0x240,
                                0x244, 0x248, 0x24c, 0x250, 0x254, 0x258, 0x270, 0x274, 0x278, 0x27c, 0x2b8, 0x2bc,
                                0x2f0, 0x368, 0x36c };
    if (!g_strvt) g_strvt = *(void **)(w + 0x98);
    fprintf(g_out, "W");
    pstr("text", tstr(w, 0x98));
    fprintf(g_out, " u80=%u pos=%u tpos=%u", U16(w, 0x80), U16(w, 0x138), U16(w, 0x13a));
    for (unsigned k = 0; k < sizeof ints / sizeof *ints; k++) fprintf(g_out, " i%x=%d", ints[k], I32(w, ints[k]));
    /* every CTTSString member other than text */
    for (int off = 0xb8; off + 0x20 <= 0x370; off += 8) {
        if (*(void **)(w + off) == g_strvt) {
            char nm[16]; sprintf(nm, "s%x", off);
            const wchar_t *s = tstr(w, off);
            if (s && *s) pstr(nm, s);
        }
    }
    /* pronunciation list at +0x360: {vt, head link*, tail, count, ..., +0x38 current link} */
    BYTE *pl = P(w, 0x360);
    if (pl) {
        BYTE *cur = P(pl, 0x38);
        fprintf(g_out, " prons=[");
        int first = 1;
        for (BYTE *lk = P(pl, 8); lk; lk = P(lk, 0)) {
            BYTE *pr = P(lk, 0x10);
            if (!first) fputc('|', g_out);
            first = 0;
            if (lk == cur) fputc('*', g_out);
            if (pr) putw8(*(const wchar_t **)(pr + 0x10), -1);
        }
        fputc(']', g_out);
    }
    /* frag state pointer +0x90 (rate/pitch/volume/emph); dump raw first 0x40 bytes as dwords */
    BYTE *fs = P(w, 0x90);
    if (fs) {
        fprintf(g_out, " fs=%d,%x,%d,%d,%x", I32(fs, 0), U16(fs, 4), I32(fs, 8), I32(fs, 0xc), U16(fs, 0x38));
        BYTE *pr = P(fs, 0x28);
        if (pr) fprintf(g_out, " pro=%g,%g,%g", *(float *)(pr + 8), *(float *)(pr + 0x28), *(float *)(pr + 0x3c));
        BYTE *sa = P(fs, 0x20);
        if (sa && P(sa, 0)) { fprintf(g_out, " sayas=\""); putw8(*(const wchar_t **)sa, -1); fputc('"', g_out); }
        fprintf(g_out, " fso=%d,%d", I32(fs, 0x70), I32(fs, 0x74));
    }
    fputc('\n', g_out);
}

static void dump_utt(BYTE *utt)
{
    BYTE *s = P(utt, 0xe0);
    if (!s) { fprintf(g_out, "S none\n"); return; }
    if (I32(s, 0x110 + 0x10) == 0) return;   /* final "no more sentences" call */
    fprintf(g_out, "S off=%d len=%d type=%d emo=%d lists=", I32(s, 0xa0), I32(s, 0xa4), I32(s, 0xa8), I32(s, 0xac));
    for (int off = 0xb0; off <= 0x110; off += 0x30) fprintf(g_out, "%s%d", off == 0xb0 ? "" : ",", I32(s, off + 0x10));
    fputc('\n', g_out);
    for (BYTE *lk = P(s, 0x110); lk; lk = P(lk, 0)) {
        BYTE *w = P(lk, 0x10);
        if (w) dump_word(w);
    }
}

typedef struct Obs { void **vt; } Obs;
static int __cdecl obs_cb(Obs *self, unsigned id, int phase, void *utt)
{
    (void)self;
    EnterCriticalSection(&g_lock);
    if (id == 0x40000 && phase == 1) {
        __try { dump_utt((BYTE *)utt); }
        __except (EXCEPTION_EXECUTE_HANDLER) { fprintf(g_out, "\nEXC in dump\n"); }
    }
    LeaveCriticalSection(&g_lock);
    if (!g_full && phase == 0 && id != 0x40000) return 1;
    return 0;
}
static void *g_obs_vt[1] = { (void *)obs_cb };
static Obs g_obs = { g_obs_vt };

typedef struct SPVTEXTFRAG { struct SPVTEXTFRAG *pNext; SPVSTATE State; LPCWSTR pTextStart;
                             ULONG ulTextLen; ULONG ulTextSrcOffset; } SPVTEXTFRAG;
typedef void ISpTTSEngineSite;
typedef HRESULT (STDMETHODCALLTYPE *SpeakFn)(void *, DWORD, REFGUID, const WAVEFORMATEX *,
                                             const SPVTEXTFRAG *, ISpTTSEngineSite *);
static SpeakFn g_orig_speak;

static void dump_frags(const SPVTEXTFRAG *f)
{
    for (; f; f = f->pNext) {
        fprintf(g_out, "F act=%d emph=%d rate=%d vol=%u pitch=%d/%d sil=%u pos=%u cat=",
                f->State.eAction, f->State.EmphAdj, f->State.RateAdj, f->State.Volume,
                f->State.PitchAdj.MiddleAdj, f->State.PitchAdj.RangeAdj, f->State.SilenceMSecs, f->State.ePartOfSpeech);
        putw8(f->State.Context.pCategory ? f->State.Context.pCategory : L"-", -1);
        fprintf(g_out, " before=");
        putw8(f->State.Context.pBefore ? f->State.Context.pBefore : L"-", -1);
        fprintf(g_out, " after=");
        putw8(f->State.Context.pAfter ? f->State.Context.pAfter : L"-", -1);
        fprintf(g_out, " ph=");
        if (f->State.pPhoneIds) for (const SPPHONEID *p = f->State.pPhoneIds; *p; p++) fprintf(g_out, "%s%u", p == f->State.pPhoneIds ? "" : ",", *p);
        fprintf(g_out, " off=%u len=%u \"", f->ulTextSrcOffset, f->ulTextLen);
        if (f->pTextStart) putw8(f->pTextStart, (int)f->ulTextLen);
        fprintf(g_out, "\"\n");
    }
}

static HRESULT STDMETHODCALLTYPE my_speak(void *self, DWORD flags, REFGUID fmt, const WAVEFORMATEX *wfx,
                                          const SPVTEXTFRAG *frags, ISpTTSEngineSite *site)
{
    BYTE *eng = *(BYTE **)((BYTE *)self + OFF_ENGINE_FROM_ITTS);
    EnterCriticalSection(&g_lock);
    dump_frags(frags);
    LeaveCriticalSection(&g_lock);
    if (eng) *(Obs **)(eng + OFF_STAGE_OBS) = &g_obs;
    return g_orig_speak(self, flags, fmt, wfx, frags, site);
}

/* ---------------- optional intermediate hooks (vtable patches) ---------------- */
#define RVA_VT_TN   0x1763b0   /* CTextNormalizer vftable; +0x18 Normalize(this, text, category, outList) */
typedef HRESULT (*NormFn)(void *, const wchar_t *, const wchar_t *, void *);
static NormFn g_orig_norm;
static HRESULT my_norm(void *self, const wchar_t *text, const wchar_t *cat, void *out)
{
    HRESULT hr = g_orig_norm(self, text, cat, out);
    EnterCriticalSection(&g_lock);
    fprintf(g_out, "TN hr=%08lx cat=\"", (unsigned long)hr); putw8(cat, -1); fprintf(g_out, "\" in=\""); putw8(text, -1);
    fprintf(g_out, "\"\n");
    LeaveCriticalSection(&g_lock);
    return hr;
}

#define RVA_VT_WSB  0x176410   /* CWhiteSpaceBreaker vftable; +0x08 Break(this, text, len, sink, flag) */
typedef HRESULT (*BreakFn)(void *, const wchar_t *, unsigned __int64, void *, int);
static BreakFn g_orig_break;
static HRESULT my_break(void *self, const wchar_t *text, unsigned __int64 len, void *sink, int flag)
{
    unsigned __int64 before = *(unsigned __int64 *)((BYTE *)sink + 0x10);
    HRESULT hr = g_orig_break(self, text, len, sink, flag);
    unsigned __int64 after = *(unsigned __int64 *)((BYTE *)sink + 0x10);
    BYTE **items = *(BYTE ***)((BYTE *)sink + 8);
    EnterCriticalSection(&g_lock);
    fprintf(g_out, "WB flag=%d in=\"", flag); putw8(text, (int)len); fprintf(g_out, "\" out=");
    for (unsigned __int64 i = before; i < after; i++) {
        BYTE *it = items[i];
        fprintf(g_out, "%s\"", i == before ? "" : "|");
        putw8(*(const wchar_t **)(it + 0x10), *(int *)(it + 0x18));
        fprintf(g_out, "\"");
    }
    fprintf(g_out, "\n");
    LeaveCriticalSection(&g_lock);
    return hr;
}

#define RVA_VT_SS   0x16d758   /* CSentSepImpl vftable; +0x08 Run(this, text, len); +0x20 len, +0x24 hard end */
typedef unsigned __int64 (*SSFn)(void *, const wchar_t *, unsigned);
static SSFn g_orig_ss;
static void *g_ss_this;
static int g_direct;
static unsigned __int64 my_ss(void *self, const wchar_t *text, unsigned len)
{
    unsigned __int64 r = g_orig_ss(self, text, len);
    g_ss_this = self;
    if (!g_direct) {
        EnterCriticalSection(&g_lock);
        fprintf(g_out, "SS %d %d len=%u in=\"", *(int *)((BYTE *)self + 0x20), *(int *)((BYTE *)self + 0x24), len);
        putw8(text, (int)len); fprintf(g_out, "\" next=%u\n", (unsigned)text[len]);
        LeaveCriticalSection(&g_lock);
    }
    return r;
}

/* CSentenceEnumerator vftable 0x175d58; +0x18 Next(this, &sentence) -> log the sentence start/end positions
 * (sentence +0x80/+0x88 start pos/frag, +0x90/+0x98 end pos/frag) as (fragment ordinal, char index) */
#define RVA_VT_SENUM 0x175d58
typedef int (*SEnumFn)(void *, void **);
static SEnumFn g_orig_senum;
static int frag_ord(BYTE *first, BYTE *f) { int k = 0; for (BYTE *p = first; p; p = P(p, 0x80), k++) if (p == f) return k; return f ? -2 : -1; }
static int my_senum(void *self, void **out)
{
    int r = g_orig_senum(self, out);
    BYTE *first = P(self, 0x30), *s = out ? (BYTE *)*out : NULL;
    EnterCriticalSection(&g_lock);
    if (r == 0 && s) {
        BYTE *sf = P(s, 0x88), *ef = P(s, 0x98), *sp = P(s, 0x80), *ep = P(s, 0x90);
        fprintf(g_out, "SN s=%d:%d e=%d:%d\n", frag_ord(first, sf), sf ? (int)((sp - P(sf, 0x68)) / 2) : -1,
                frag_ord(first, ef), ef ? (int)((ep - P(ef, 0x68)) / 2) : -1);
    } else fprintf(g_out, "SN r=%d\n", r);
    LeaveCriticalSection(&g_lock);
    return r;
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

static void install_hooks(void)
{
    DWORD old;
    void **slot = (void **)(g_base + RVA_VT_TTSENG + 3 * sizeof(void *));
    if (*slot != g_base + RVA_SPEAK) { fprintf(stderr, "unexpected Speak slot\n"); ExitProcess(2); }
    g_orig_speak = (SpeakFn)*slot;
    VirtualProtect(slot, sizeof(void *), PAGE_READWRITE, &old);
    *slot = (void *)my_speak;
    VirtualProtect(slot, sizeof(void *), old, &old);
    if (memcmp(g_base + RVA_LOG, "\x48\x8b\xc4\x48\x89\x50\x10", 7) != 0) { fprintf(stderr, "bad logger\n"); ExitProcess(2); }
    write_jmp(g_base + RVA_LOG, (void *)my_log);
    if (g_hooks) patch_slot(RVA_VT_TN, 3, (void *)my_norm, (void **)&g_orig_norm);
    if (g_hooks) patch_slot(RVA_VT_WSB, 1, (void *)my_break, (void **)&g_orig_break);
    patch_slot(RVA_VT_SS, 1, (void *)my_ss, (void **)&g_orig_ss);
    patch_slot(RVA_VT_SENUM, 3, (void *)my_senum, (void **)&g_orig_senum);
}

static wchar_t *u8tow(const char *b, int n)
{
    int wn = MultiByteToWideChar(CP_UTF8, 0, b, n, NULL, 0);
    wchar_t *w = malloc((wn + 1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, b, n, w, wn);
    w[wn] = 0;
    return w;
}

int wmain(int argc, wchar_t **argv)
{
    if (argc < 4) { fprintf(stderr, "usage: zftap1 david|zira corpus.txt dump.txt [full] [log] [hooks]\n"); return 1; }
    for (int i = 4; i < argc; i++) {
        if (!_wcsicmp(argv[i], L"full")) g_full = 1;
        if (!_wcsicmp(argv[i], L"log")) g_log = 1;
        if (!_wcsicmp(argv[i], L"hooks")) g_hooks = 1;
        if (!_wcsicmp(argv[i], L"direct")) g_direct = 1;
    }
    const wchar_t *voice = argv[1];
    wchar_t tokid[512];
    const wchar_t *tn = !_wcsicmp(voice, L"zira") ? L"MSTTS_V110_enUS_ZiraM"
                      : !_wcsicmp(voice, L"mark") ? L"MSTTS_V110_enUS_MarkM" : L"MSTTS_V110_enUS_DavidM";
    swprintf(tokid, 512, L"%ls%ls", TOKROOT, tn);
    InitializeCriticalSection(&g_lock);
    g_out = _wfopen(argv[3], L"wb");
    if (!g_out) { fprintf(stderr, "cannot open output\n"); return 1; }

    FILE *cf = _wfopen(argv[2], L"rb");
    if (!cf) { fprintf(stderr, "cannot open corpus\n"); return 1; }
    fseek(cf, 0, SEEK_END); long cn = ftell(cf); fseek(cf, 0, SEEK_SET);
    char *cb = malloc(cn + 1); fread(cb, 1, cn, cf); cb[cn] = 0; fclose(cf);

    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    g_base = (BYTE *)LoadLibraryW(ENGINE_DLL);
    if (!g_base) { fprintf(stderr, "cannot load engine\n"); return 1; }
    install_hooks();

    ISpObjectToken *tok = NULL; ISpVoice *v = NULL; ISpStream *st = NULL; IStream *mem = NULL;
    HRESULT hr = CoCreateInstance(&CLSID_SpObjectToken, NULL, CLSCTX_ALL, &IID_ISpObjectToken, (void **)&tok);
    if (SUCCEEDED(hr)) hr = ISpObjectToken_SetId(tok, NULL, tokid, FALSE);
    if (SUCCEEDED(hr)) hr = CoCreateInstance(&CLSID_SpVoice, NULL, CLSCTX_ALL, &IID_ISpVoice, (void **)&v);
    if (SUCCEEDED(hr)) hr = ISpVoice_SetVoice(v, tok);
    if (FAILED(hr)) { fprintf(stderr, "voice setup failed %08lx\n", hr); return 1; }
    WAVEFORMATEX wf = { WAVE_FORMAT_PCM, 1, 16000, 32000, 2, 16, 0 };
    CreateStreamOnHGlobal(NULL, TRUE, &mem);
    CoCreateInstance(&CLSID_SpStream, NULL, CLSCTX_ALL, &IID_ISpStream, (void **)&st);
    hr = ISpStream_SetBaseStream(st, mem, &SPDFID_WaveFormatEx, &wf);
    if (SUCCEEDED(hr)) hr = ISpVoice_SetOutput(v, (IUnknown *)st, TRUE);

    if (g_direct) {
        /* capture a CSentSepImpl instance, then call it directly on every line (escapes \n \t \r \ \uXXXX) */
        ISpVoice_Speak(v, L"Hi.", SPF_DEFAULT, NULL);
        if (!g_ss_this) { fprintf(stderr, "no sentsep instance\n"); return 1; }
    }
    int lineno = 0;
    char *p = cb;
    if ((BYTE)p[0] == 0xEF && (BYTE)p[1] == 0xBB && (BYTE)p[2] == 0xBF) p += 3;
    while (*p) {
        char *e = p;
        while (*e && *e != '\n') e++;
        int n = (int)(e - p);
        if (n && p[n - 1] == '\r') n--;
        lineno++;
        if (n > 0 && !(n >= 2 && p[0] == '#' && p[1] == '#')) {
            wchar_t *w = u8tow(p, n);
            if (g_direct) {
                int k = 0;
                for (int j = 0; w[j]; j++) {
                    if (w[j] == '\\' && w[j + 1]) {
                        j++;
                        if (w[j] == 'n') w[k++] = 10; else if (w[j] == 't') w[k++] = 9; else if (w[j] == 'r') w[k++] = 13;
                        else if (w[j] == 'u') { w[k++] = (wchar_t)wcstoul((wchar_t[]){w[j+1],w[j+2],w[j+3],w[j+4],0}, NULL, 16); j += 4; }
                        else w[k++] = w[j];
                    } else w[k++] = w[j];
                }
                w[k] = 0;
                int pos = 0;
                fprintf(g_out, "L %d\t", lineno); putw8(w, k); fputc('\n', g_out);
                /* repeated calls like the enumerator loop: advance by consumed until the end */
                while (pos < k) {
                    g_orig_ss(g_ss_this, w + pos, (unsigned)(k - pos));
                    int c = *(int *)((BYTE *)g_ss_this + 0x20), h = *(int *)((BYTE *)g_ss_this + 0x24);
                    fprintf(g_out, "SD %d %d %d\n", pos, c, h);
                    if (c <= 0) break;
                    pos += c;
                }
                free(w);
                p = *e ? e + 1 : e;
                continue;
            }
            fprintf(g_out, "L %d\t", lineno); putw8(w, -1); fputc('\n', g_out);
            hr = ISpVoice_Speak(v, w, SPF_DEFAULT, NULL);
            if (FAILED(hr)) fprintf(g_out, "SPEAKFAIL %08lx\n", hr);
            fflush(g_out);
            free(w);
        }
        p = *e ? e + 1 : e;
    }
    fclose(g_out);
    return 0;
}
