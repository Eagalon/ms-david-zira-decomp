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
static int g_full, g_log, g_hooks, g_ltsmode;

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


/* ---- LTS oracle: CLTSLexiconCART vt+0x18 (0x18015fb70) predict(this, word, out, cap) ---- */
#define RVA_VT_LTSCART 0x1764d0
typedef unsigned (*LtsFn)(void *, const wchar_t *, wchar_t *, unsigned long long);
static LtsFn g_orig_lts;
static void *g_lts_this;
static int g_lts_log;
static unsigned my_lts(void *self, const wchar_t *w, wchar_t *out, unsigned long long cap)
{
    unsigned r = g_orig_lts(self, w, out, cap);
    g_lts_this = self;
    if (g_lts_log) {
        EnterCriticalSection(&g_lock);
        fprintf(g_out, "LTS in=\""); putw8(w, -1); fprintf(g_out, "\" out=\""); putw8(out, -1); fprintf(g_out, "\"\n");
        LeaveCriticalSection(&g_lock);
    }
    return r;
}


/* ---- trace CTTSWord vt+0x88 SetPronunciation(this, ids, source, force) ---- */
#include <intrin.h>
#define RVA_VT_WORD 0x16d098
typedef unsigned (*SetPronFn)(void *, const unsigned short *, int, int);
static SetPronFn g_orig_setpron;
static int g_trace_pron;
static unsigned my_setpron(void *self, const unsigned short *ph, int src, int force)
{
    void *ra = _ReturnAddress();
    unsigned r = g_orig_setpron(self, ph, src, force);
    if (g_trace_pron) {
        EnterCriticalSection(&g_lock);
        fprintf(g_out, "SETPRON ra=%llx word=\"", (unsigned long long)((BYTE *)ra - g_base));
        putw8(*(const wchar_t **)((BYTE *)self + 0x98 + 8), -1);
        fprintf(g_out, "\" src=%d force=%d ph=", src, force);
        if (ph) for (int i = 0; ph[i]; i++) fprintf(g_out, "%s%u", i ? "," : "", ph[i]);
        fprintf(g_out, "\n");
        LeaveCriticalSection(&g_lock);
    }
    return r;
}


/* ---- morph oracle: loc!CEnMorph vt+8 (0x18005c8e0) lookup(this, word, lang, 0, &entry) ---- */
#define RVA_LOC_VT_ENMORPH 0x80590
typedef long (*MorphFn)(void *, const wchar_t *, short, void *, void **);
static MorphFn g_orig_morph;
static void *g_morph_this;
static int g_morphmode;
static long my_morph(void *self, const wchar_t *w, short lang, void *x, void **out)
{
    g_morph_this = self;
    return g_orig_morph(self, w, lang, x, out);
}
typedef long (*VGetU)(void *, unsigned *);
typedef long (*VGetI)(void *, unsigned, void **);
typedef long (*VGetS)(void *, wchar_t **);
typedef long (*VGetU32)(void *, unsigned, unsigned *);
#define VT(o, off) (*(void **)(*(BYTE **)(o) + (off)))
static void dump_entry(void *e)
{
    unsigned n = 0, i, k, j;
    ((VGetU)VT(e, 0x18))(e, &n);
    for (i = 0; i < n; i++) {
        void *p = NULL; unsigned src = 0, na = 0; wchar_t *ph = NULL;
        ((VGetI)VT(e, 0x20))(e, i, &p);
        if (!p) continue;
        ((VGetU)VT(p, 0x18))(p, &src);
        ((VGetS)VT(p, 0x38))(p, &ph);
        fprintf(g_out, " {%x ", src);
        if (ph) for (k = 0; ph[k]; k++) fprintf(g_out, "%s%x", k ? "." : "", ph[k]);
        ((VGetU)VT(p, 0x40))(p, &na);
        for (k = 0; k < na; k++) {
            void *as = NULL; unsigned m = 0;
            ((VGetI)VT(p, 0x48))(p, k, &as);
            if (!as) continue;
            ((VGetU)VT(as, 0x18))(as, &m);
            fprintf(g_out, " [");
            for (j = 0; j < m; j++) { unsigned v = 0; ((VGetU32)VT(as, 0x20))(as, j, &v); fprintf(g_out, "%s%x", j ? "," : "", v); }
            fprintf(g_out, "]");
        }
        fprintf(g_out, "}");
    }
}

/* ---- OOV oracle: loc!CLocaleTextAnalyzerENU vt+0x28 (OOV splitter) and CWordPronouncer vt+8 (mode 8 = COMPOUNDPRON) ---- */
#define RVA_LOC_VT_LTA 0x7b7e8
#define RVA_VT_WORDPRON 0x176368
typedef long (*LtaSplitFn)(void *, void *, unsigned short *, unsigned);
typedef long (*WpModeFn)(void *, const wchar_t *, int, void *, unsigned short *, unsigned, int *);
static LtaSplitFn g_orig_lta28;
static WpModeFn g_orig_wp8;
static void *g_lta_this, *g_wp_this;
static int g_oovmode;
static long my_lta28(void *self, void *w, unsigned short *buf, unsigned cap)
{
    g_lta_this = self;
    return g_orig_lta28(self, w, buf, cap);
}
static int g_wp_depth, g_wp_log;
static long my_wp8(void *self, const wchar_t *t, int mode, void *dom, unsigned short *buf, unsigned cap, int *src)
{
    long r;
    g_wp_this = self;
    g_wp_depth++;
    r = g_orig_wp8(self, t, mode, dom, buf, cap, src);
    g_wp_depth--;
    if (g_wp_log && g_wp_depth > 0) {
        int k;
        fprintf(g_out, " {m%d \"", mode); putw8(t, -1); fprintf(g_out, "\" r=%lx ", (unsigned long)r);
        for (k = 0; buf && buf[k] && k < 400; k++) fprintf(g_out, "%s%x", k ? "." : "", buf[k]);
        fprintf(g_out, "}");
    }
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
    patch_slot(RVA_VT_LTSCART, 3, (void *)my_lts, (void **)&g_orig_lts);
    patch_slot(RVA_VT_WORD, 0x88 / 8, (void *)my_setpron, (void **)&g_orig_setpron);
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
        if (!_wcsicmp(argv[i], L"lts")) g_ltsmode = 1;
        if (!_wcsicmp(argv[i], L"ltslog")) g_lts_log = 1;
        if (!_wcsicmp(argv[i], L"trace")) g_trace_pron = 1;
        if (!_wcsicmp(argv[i], L"morph")) g_morphmode = 1;
        if (!_wcsicmp(argv[i], L"oov")) g_oovmode = 1;
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

    if (g_oovmode) {
        ISpVoice_Speak(v, L"hello", SPF_DEFAULT, NULL);
        BYTE *loc = (BYTE *)GetModuleHandleW(L"MSTTSLoc_OneCore.dll");
        if (!loc) { fprintf(stderr, "no loc dll\n"); return 1; }
        {
            DWORD old; void **slot = (void **)(loc + RVA_LOC_VT_LTA + 0x28);
            g_orig_lta28 = (LtaSplitFn)*slot;
            VirtualProtect(slot, 8, PAGE_READWRITE, &old); *slot = (void *)my_lta28; VirtualProtect(slot, 8, old, &old);
        }
        patch_slot(RVA_VT_WORDPRON, 1, (void *)my_wp8, (void **)&g_orig_wp8);
        ISpVoice_Speak(v, L"glorptastic snerbleblorf", SPF_DEFAULT, NULL);
        if (!g_lta_this || !g_wp_this) { fprintf(stderr, "no this %p %p\n", g_lta_this, g_wp_this); return 1; }
        typedef void *(*CtorFn)(void *);
        typedef long (*SetTextFn)(void *, const wchar_t *);
        typedef void *(*StrCtorFn)(void *, const wchar_t *);
        CtorFn wctor = (CtorFn)(g_base + 0x1ba9c);
        StrCtorFn sctor = (StrCtorFn)(g_base + 0x197b4);
        char *q = cb;
        while (*q) {
            char *e = q; while (*e && *e != '\n') e++;
            int n = (int)(e - q); if (n && q[n - 1] == '\r') n--;
            if (n > 0) {
                wchar_t *w = u8tow(q, n);
                BYTE *word = (BYTE *)calloc(1, 0x400);
                unsigned short buf[0x200];
                BYTE dom[0x40];
                int src = -1, k;
                long r1, r2;
                wctor(word);
                ((SetTextFn)(*(void ***)word)[0x78 / 8])(word, w);
                memset(buf, 0, sizeof buf);
                r1 = g_orig_lta28(g_lta_this, word, buf, 0x180);
                putw8(w, -1); fprintf(g_out, "\t%lx\t", (unsigned long)r1);
                for (k = 0; buf[k]; k++) fprintf(g_out, "%s%x", k ? "." : "", buf[k]);
                memset(buf, 0, sizeof buf);
                sctor(dom, L"none");
                g_wp_log = 1; g_wp_depth = 1;
                r2 = g_orig_wp8(g_wp_this, w, 8, dom, buf, 0x180, &src);
                g_wp_depth = 0; g_wp_log = 0;
                fprintf(g_out, "\t%lx\t%d\t", (unsigned long)r2, src);
                for (k = 0; buf[k]; k++) fprintf(g_out, "%s%x", k ? "." : "", buf[k]);
                {   /* compound breaker (LTA+0xb0): vt+0x20 check, vt+0x10 split -> list, vt+8 merge, vt+0x18 check */
                    typedef long (*ChkFn)(void *, const wchar_t *);
                    typedef long (*SplitFn)(void *, const wchar_t *, void *, void *);
                    typedef long (*ListFn)(void *, void *);
                    void *cbk = *(void **)((BYTE *)g_lta_this + 0xb0);
                    BYTE lst[0x40]; BYTE d2[0x40];
                    long c20, c10 = -99, c08 = -99, c18 = -99;
                    memset(lst, 0, sizeof lst); *(int *)(lst + 0x28) = 10;
                    c20 = ((ChkFn)(*(void ***)cbk)[4])(cbk, w);
                    if (c20 == 0) {
                        sctor(d2, L"none");
                        c10 = ((SplitFn)(*(void ***)cbk)[2])(cbk, w, d2, lst);
                        fprintf(g_out, "\tparts:");
                        for (BYTE *nd = *(BYTE **)lst; nd; nd = *(BYTE **)nd) { fputc('[', g_out); putw8(*(const wchar_t **)(nd + 0x10), -1); fputc(']', g_out); }
                        if (c10 == 0) {
                            c08 = ((ListFn)(*(void ***)cbk)[1])(cbk, lst);
                            fprintf(g_out, " merged:");
                            for (BYTE *nd = *(BYTE **)lst; nd; nd = *(BYTE **)nd) { fputc('[', g_out); putw8(*(const wchar_t **)(nd + 0x10), -1); fputc(']', g_out); }
                            c18 = ((ListFn)(*(void ***)cbk)[3])(cbk, lst);
                        }
                    }
                    fprintf(g_out, "\tchk=%lx split=%lx merge=%lx valid=%lx", (unsigned long)c20, (unsigned long)c10, (unsigned long)c08, (unsigned long)c18);
                }
                {   /* compound breaker's lexicon: LTA+0xa0, vt+8(this, word, lang, 0, &entry) */
                    typedef long (*LexFn)(void *, const wchar_t *, unsigned short, void *, void **);
                    void *lex = *(void **)((BYTE *)g_lta_this + 0xa0), *ent = NULL;
                    long r3 = lex ? ((LexFn)(*(void ***)lex)[1])(lex, w, 0x409, NULL, &ent) : -1;
                    fprintf(g_out, "\t%lx", (unsigned long)r3);
                    if (r3 >= 0 && ent) dump_entry(ent);
                }
                fputc('\n', g_out);
                fflush(g_out);
                free(w);
            }
            q = *e ? e + 1 : e;
        }
        fclose(g_out);
        return 0;
    }
    if (g_morphmode) {
        ISpVoice_Speak(v, L"hello", SPF_DEFAULT, NULL);
        BYTE *loc = (BYTE *)GetModuleHandleW(L"MSTTSLoc_OneCore.dll");
        if (!loc) { fprintf(stderr, "no loc dll\n"); return 1; }
        {
            DWORD old; void **slot = (void **)(loc + RVA_LOC_VT_ENMORPH + 8);
            g_orig_morph = (MorphFn)*slot;
            VirtualProtect(slot, 8, PAGE_READWRITE, &old); *slot = (void *)my_morph; VirtualProtect(slot, 8, old, &old);
        }
        ISpVoice_Speak(v, L"glorptastics", SPF_DEFAULT, NULL);
        if (!g_morph_this) { fprintf(stderr, "no morph this\n"); return 1; }
        char *q = cb;
        while (*q) {
            char *e = q; while (*e && *e != '\n') e++;
            int n = (int)(e - q); if (n && q[n - 1] == '\r') n--;
            if (n > 0) {
                wchar_t *w = u8tow(q, n); void *ent = NULL;
                long r = g_orig_morph(g_morph_this, w, 0x409, NULL, &ent);
                putw8(w, -1); fprintf(g_out, "\t%lx", (unsigned long)r);
                if (r >= 0 && ent) dump_entry(ent);
                fputc('\n', g_out);
                free(w);
            }
            q = *e ? e + 1 : e;
        }
        fclose(g_out);
        return 0;
    }
    if (g_ltsmode) {
        ISpVoice_Speak(v, L"glorptastic", SPF_DEFAULT, NULL);
        if (!g_lts_this) { fprintf(stderr, "no LTS this\n"); return 1; }
        char *q = cb;
        while (*q) {
            char *e = q; while (*e && *e != '\n') e++;
            int n = (int)(e - q); if (n && q[n - 1] == '\r') n--;
            if (n > 0) {
                wchar_t *w = u8tow(q, n); static wchar_t out[0x1000];
                out[0] = 0;
                unsigned r = g_orig_lts(g_lts_this, w, out, 0xc01);
                putw8(w, -1); fprintf(g_out, "\t%x\t", r); putw8(out, -1); fputc('\n', g_out);
                free(w);
            }
            q = *e ? e + 1 : e;
        }
        fclose(g_out);
        return 0;
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
