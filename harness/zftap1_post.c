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

static BYTE *g_words[4096]; static int g_nwords;
static BYTE *g_grp[4096]; static int g_ngrp;
static int word_index(BYTE *w) { for (int i = 0; i < g_nwords; i++) if (g_words[i] == w) return i; return -1; }
static int grp_id(BYTE *g) { if (!g) return 0; for (int i = 0; i < g_ngrp; i++) if (g_grp[i] == g) return i + 1; if (g_ngrp < 4096) g_grp[g_ngrp++] = g; return g_ngrp; }
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
    /* relational fields: +0x2e8 group object, +0x2b0 attached pause word, +0x1a8 NE segment {first, last, ..} */
    {
        BYTE *seg = P(w, 0x1a8);
        fprintf(g_out, " grp=%d ap=%d ne=%d", grp_id(P(w, 0x2e8)), P(w, 0x2b0) ? word_index(P(w, 0x2b0)) : -1,
                seg ? (P(seg, 0) == w ? 1 : 2) : 0);
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
    g_nwords = 0; g_ngrp = 0;
    for (BYTE *lk = P(s, 0x110); lk; lk = P(lk, 0)) if (P(lk, 0x10) && g_nwords < 4096) g_words[g_nwords++] = P(lk, 0x10);
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

static void patch_slot(DWORD rva_vt, int slot, void *fn, void **orig)
{
    DWORD old;
    void **p = (void **)(g_base + rva_vt + slot * 8);
    *orig = *p;
    VirtualProtect(p, 8, PAGE_READWRITE, &old);
    *p = fn;
    VirtualProtect(p, 8, old, &old);
}


/* ================= zftap1_post: post-Analyze step hooks (fork E) ================= */
#define RVA_CS_DETECT  0x05cadc   /* call 1800b7358 CSentAndPuncDetector(det, utt) */
#define RVA_CS_SUFFIX  0x05cbfc   /* call 18001bf24 suffix(tables, utt) */
#define RVA_CS_QUOTE   0x05cc0e   /* call 1800b8608 quotes(q, utt) */
#define RVA_CS_PAR     0x05cc20   /* call 1800b90a8 parallel(p, utt) */
#define RVA_CS_STEP9   0x065ae3   /* call 1800bb3e0 step9(analyzer) */
#define RVA_VT_SENT    0x16fde8   /* CTTSSentence vftable */
typedef __int64 (*Fn2)(void *, void *);
typedef __int64 (*Fn1)(void *);
static Fn2 o_detect, o_suffix, o_quote, o_par; static Fn1 o_step9;
typedef __int64 (*SentFn)(void *, void *, void *);
static SentFn o_vtb0, o_vta0;
static int g_postdump;

static void pw(int idx, BYTE *w)
{
    fprintf(g_out, "p %d t=%d i180=%d pos=%u tpos=%u", idx, I32(w, 0x88), I32(w, 0x180), U16(w, 0x138), U16(w, 0x13a));
    pstr("text", tstr(w, 0x98)); pstr("reg", tstr(w, 0xb8));
    fprintf(g_out, " off=%d len=%d seg=%p kids=%d", I32(w, 0x270), I32(w, 0x274), P(w, 0x1a8), P(w, 0x18) ? 1 : 0);
    BYTE *pl = P(w, 0x360);
    int plen = 0;
    if (pl && P(pl, 0x38)) { BYTE *pr = P(P(pl, 0x38), 0x10); plen = pr && *(const wchar_t **)(pr + 0x10) ? (int)wcslen(*(const wchar_t **)(pr + 0x10)) : 0; }
    fprintf(g_out, " pron=%d", plen);
    pstr("ne", tstr(w, 0x188));
    { BYTE *fs = P(w, 0x90), *sa = fs ? P(fs, 0x20) : NULL;
      fprintf(g_out, " sa=%p", sa);
      pstr("sas", sa && P(sa, 0) ? *(const wchar_t **)sa : NULL);
      pstr("dom", tstr(w, 0x1b0)); }
    fputc('\n', g_out);
}
static void dump_sent_words(const char *tag, BYTE *s)
{
    int i = 0;
    fprintf(g_out, "P %s type=%d\n", tag, I32(s, 0xa8));
    for (BYTE *lk = P(s, 0x110); lk; lk = P(lk, 0)) pw(i++, P(lk, 0x10));
}
static int widx(BYTE *s, BYTE *w)
{
    int i = 0;
    if (!w) return -1;
    for (BYTE *lk = P(s, 0x110); lk; lk = P(lk, 0), i++) if (P(lk, 0x10) == w) return i;
    return -99;
}
/* sentence list at off: {head link, tail, count}; link {next, prev, item} */
static void dump_list(BYTE *s, int off, const char *name)
{
    fprintf(g_out, "LIST %s n=%lld\n", name, *(__int64 *)(s + off + 0x10));
    for (BYTE *lk = P(s, off); lk; lk = P(lk, 0)) {
        BYTE *it = P(lk, 0x10);
        if (!it) continue;
        if (off == 0x278) {   /* segment {first, last, value wchar*} */
            fprintf(g_out, "  seg %d %d \"", widx(s, P(it, 0)), widx(s, P(it, 8)));
            if (P(it, 0x10)) putw8(*(const wchar_t **)(it + 0x10), -1);
            fprintf(g_out, "\"\n");
        } else if (off == 0x1e8) {  /* quote pair {openword, openidx, closeword, closeidx} */
            fprintf(g_out, "  quote %d(%lld) %d(%lld)\n", widx(s, P(it, 0)), *(__int64 *)(it + 8), widx(s, P(it, 0x10)), *(__int64 *)(it + 0x18));
        } else if (off == 0x248) {  /* CParallelStruct: +8 head link, +0x18 count; item {start,end,kind} */
            fprintf(g_out, "  par n=%lld:", *(__int64 *)(it + 0x18));
            for (BYTE *l2 = P(it, 8); l2; l2 = P(l2, 0)) {
                BYTE *c = P(l2, 0x10);
                fprintf(g_out, " [%d..%d k=%d]", widx(s, P(c, 0)), widx(s, P(c, 8)), I32(c, 0x10));
            }
            fputc('\n', g_out);
        } else {
            fprintf(g_out, "  item %p\n", it);
        }
    }
}
static void dump_lists(BYTE *s)
{
    int i = 0;
    dump_list(s, 0x1e8, "1e8"); dump_list(s, 0x218, "218"); dump_list(s, 0x248, "248"); dump_list(s, 0x278, "278");
    for (BYTE *lk = P(s, 0x110); lk; lk = P(lk, 0), i++) {
        BYTE *w = P(lk, 0x10), *sg = P(w, 0x1a8);
        if (sg) fprintf(g_out, "  wseg %d -> %d..%d\n", i, widx(s, P(sg, 0)), widx(s, P(sg, 8)));
    }
}
static BYTE *utt_sent(void *utt) { return P(utt, 0xe0); }
static int g_postab_done;
static void dump_pos_tables(BYTE *s)
{
    BYTE *po = P(s, 0x2d8);
    if (g_postab_done || !po) return;
    g_postab_done = 1;
    void **vt = *(void ***)po;
    for (int id = 0; id < 80; id++) {
        int cls = ((int (*)(void *, unsigned short))vt[2])(po, (unsigned short)id);
        const wchar_t *nm = ((const wchar_t *(*)(void *, unsigned short))vt[1])(po, (unsigned short)id);
        fprintf(g_out, "POSTAB %d class=%d name=\"", id, cls); if (nm) putw8(nm, -1); fprintf(g_out, "\"\n");
    }
    unsigned short d = ((unsigned short (*)(void *))vt[7])(po);
    fprintf(g_out, "POSTAB default=%u\n", d);
}
static __int64 h_detect(void *d, void *utt)
{
    BYTE *s = utt_sent(utt); __int64 r;
    dump_pos_tables(s);
    dump_sent_words("pre-detect", s);
    r = o_detect(d, utt);
    fprintf(g_out, "P post-detect r=%lld type=%d\n", r, I32(s, 0xa8));
    return r;
}
static __int64 h_suffix(void *t, void *utt)
{
    BYTE *s = utt_sent(utt); __int64 r = o_suffix(t, utt);
    dump_sent_words("post-suffix", s);
    return r;
}
static __int64 h_quote(void *q, void *utt) { __int64 r = o_quote(q, utt); fprintf(g_out, "P post-quote r=%lld\n", r); return r; }
static __int64 h_par(void *p, void *utt) { __int64 r = o_par(p, utt); fprintf(g_out, "P post-par r=%lld\n", r); dump_lists(utt_sent(utt)); return r; }
static void dump_ana_list(const char *tag, BYTE *a)
{
    int i = 0;
    fprintf(g_out, "P %s\n", tag);
    for (BYTE *lk = P(a, 0x420); lk; lk = P(lk, 0)) pw(i++, P(lk, 0x10));
}
static __int64 h_step9(void *a) { __int64 r; dump_ana_list("pre-step9", (BYTE *)a); r = o_step9(a); dump_ana_list("post-step9", (BYTE *)a); return r; }
static __int64 h_vtb0(void *s, void *x, void *y) { __int64 r; dump_sent_words("pre-vtb0", (BYTE *)s); r = o_vtb0(s, x, y); dump_lists((BYTE *)s); return r; }
static __int64 h_vta0(void *s, void *x, void *y) { dump_sent_words("pre-vta0", (BYTE *)s); return o_vta0(s, x, y); }

static BYTE *g_stubs;
static void *hook_call(DWORD rva_call, void *fn, int k)
{
    BYTE *at = g_base + rva_call, *stub = g_stubs + 16 * k;
    void *orig = at + 5 + *(int *)(at + 1);
    DWORD old;
    stub[0] = 0xFF; stub[1] = 0x25; *(DWORD *)(stub + 2) = 0; *(void **)(stub + 6) = fn;
    VirtualProtect(at, 5, PAGE_EXECUTE_READWRITE, &old);
    *(int *)(at + 1) = (int)(stub - (at + 5));
    VirtualProtect(at, 5, old, &old);
    FlushInstructionCache(GetCurrentProcess(), at, 5);
    return orig;
}
static void install_post_hooks(void)
{
    for (BYTE *want = g_base - 0x10000; !g_stubs && want > g_base - 0x70000000; want -= 0x10000)
        g_stubs = VirtualAlloc(want, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!g_stubs) { fprintf(stderr, "no stub page\n"); ExitProcess(3); }
    o_detect = (Fn2)hook_call(RVA_CS_DETECT, (void *)h_detect, 0);
    o_suffix = (Fn2)hook_call(RVA_CS_SUFFIX, (void *)h_suffix, 1);
    o_quote = (Fn2)hook_call(RVA_CS_QUOTE, (void *)h_quote, 2);
    o_par = (Fn2)hook_call(RVA_CS_PAR, (void *)h_par, 3);
    o_step9 = (Fn1)hook_call(RVA_CS_STEP9, (void *)h_step9, 4);
    patch_slot(RVA_VT_SENT, 0xb0 / 8, (void *)h_vtb0, (void **)&o_vtb0);
    patch_slot(RVA_VT_SENT, 0xa0 / 8, (void *)h_vta0, (void **)&o_vta0);
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
    install_post_hooks();
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
