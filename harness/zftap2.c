/* zftap2: golden-data dumper for the frontend part-2 port (tree -> prosody -> units/events -> feature matrix).
 * x64, drives MSTTSEngine_OneCore.dll 10.3.21207 through SAPI5 with a OneCore token (idea from ziratap/ziraprobe).
 *
 * Usage: zftap2.exe david|zira|mark @corpus.txt out.txt [nowave] [feats] [pred]
 *   corpus : UTF-8, one Speak() per line ('<' anywhere -> SPF_IS_XML).  Empty lines / lines starting "##" skipped.
 *   nowave : skip the stream adapter (lattice/selector/wave) -> fast; events then carry no audio offsets
 *   feats  : also dump every GetFeature() value of every node at each stage (big, for mapping)
 *   pred   : dump word prosody fields after each sub-predictor (CLinguisticProsodyTagger+0x30 callback)
 *
 * Output (UTF-8 lines; '\s' = space inside strings):
 *   LINE <n> <text>
 *   U <k>                                 utterance k of this line (one per sentence)
 *   STAGE <name>                          IN (before 0x80000) | PRED<id>a | PRO (after 0x80000) | UNIT (after 0x100000)
 *   SENT type= emo= a0= a4= off= len=
 *   W <i> <fields...>                     word list (sentence+0x110) in order, see dump_word()
 *   Y <i> w=<word idx> ph=<first phone idx>-<last>   syllables (sentence+0xe0) with parent word
 *   H <i> s=<syll idx> id=<phone id> st=<+0x80>       phones (sentence+0xb0)
 *   PW/PH/IP <i> <first word idx> <last word idx> par=<idx>
 *   QP <open> <close> <n>                 quote/bracket pairs (sentence+0x1e8)
 *   PS <k> <a> <b> <type>                 parallel structure k elements (sentence+0x248)
 *   FX <n> / F <i> <name> <values>        feature matrix (CTTSFeatureExtractionEngine slot 3)
 *   EV id wParam lParam audioOffset [str] SAPI events after Speak
 */
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#include <windows.h>
#include <sapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENGINE_DLL L"C:\\Windows\\System32\\Speech_OneCore\\Engines\\TTS\\MSTTSEngine_OneCore.dll"
#define TOKROOT L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices\\Tokens\\"
#define RVA_SPEAK 0x08b210
#define RVA_VT_TTSENG 0x175210
#define OFF_ENGINE_FROM_ITTS 0x68
#define OFF_STAGE_OBS 0x578

typedef unsigned char u8;
static BYTE *g_base, *g_eng;
static FILE *g_out;
static int g_nowave, g_feats, g_pred, g_utt;

#define P(p, off) (*(BYTE **)((BYTE *)(p) + (off)))
#define I32(p, off) (*(int *)((BYTE *)(p) + (off)))
#define U16(p, off) (*(unsigned short *)((BYTE *)(p) + (off)))

static void pstr(const wchar_t *s)
{
    if (!s) { fputs("(null)", g_out); return; }
    if (!*s) { fputs("(empty)", g_out); return; }
    for (; *s; s++) {
        wchar_t c = *s;
        if (c == L' ') fputs("\\s", g_out);
        else if (c == L'\\') fputs("\\\\", g_out);
        else if (c < 0x20) fprintf(g_out, "\\x%02x", c);
        else if (c < 0x80) fputc((char)c, g_out);
        else { char b[8]; int n = WideCharToMultiByte(CP_UTF8, 0, &c, 1, b, 8, NULL, NULL); fwrite(b, 1, n, g_out); }
    }
}
static const wchar_t *tstr(BYTE *obj, int off) { __try { return *(const wchar_t **)(obj + off + 8); } __except (1) { return NULL; } }

typedef struct { int kind; int pad; union { int i; wchar_t *s; } u; } FVal;
typedef long (*GetF_t)(void *, int, FVal *);
static int safe_get(void *iface, int pid, FVal *v)
{
    long hr;
    __try { GetF_t f = (GetF_t)(*(void ***)iface)[5]; memset(v, 0, sizeof *v); hr = f(iface, pid, v); }
    __except (EXCEPTION_EXECUTE_HANDLER) { return -2; }
    return hr;
}
static void dump_feats(void *iface, int levelmask)
{
    static const struct { int id; int mask; } PR[] = {
#include "zftap2_props.h"
    };
    int k;
    for (k = 0; k < (int)(sizeof PR / sizeof PR[0]); k++) {
        FVal v; long hr;
        if (!(PR[k].mask & levelmask)) continue;
        hr = safe_get(iface, PR[k].id, &v);
        if (hr == -2 || hr < 0) continue;
        if (v.kind == 2) { fprintf(g_out, " f%x=s:", PR[k].id); __try { pstr(v.u.s); } __except (1) { fputs("?", g_out); } }
        else if (v.kind == -1) fprintf(g_out, " f%x=N", PR[k].id);
        else fprintf(g_out, " f%x=%d:%d", PR[k].id, v.kind, v.u.i);
    }
}

typedef struct Link { struct Link *next, *prev; BYTE *item; } Link;
static void **get_list(BYTE *sent, int vtoff)
{
    void **lst = NULL;
    typedef long (*LG)(void *, void ***);
    __try { ((LG)((*(void ***)sent)[vtoff / 8]))(sent, &lst); } __except (1) { lst = NULL; }
    return lst;
}
#define MAXN 4096
static BYTE *g_w[MAXN], *g_s[MAXN], *g_p[MAXN], *g_pw[MAXN], *g_ph[MAXN], *g_ip[MAXN];
static int g_nw, g_ns, g_np, g_npw, g_nph, g_nip;
static int collect(BYTE *sent, int vtoff, BYTE **arr)
{
    void **lst = get_list(sent, vtoff);
    Link *l; int n = 0;
    if (!lst) return 0;
    for (l = (Link *)lst[0]; l && n < MAXN; l = l->next) arr[n++] = l->item;
    return n;
}
static int idx_of(BYTE **arr, int n, BYTE *p)
{
    int i;
    if (!p) return -1;
    for (i = 0; i < n; i++) if (arr[i] == p) return i;
    return -2;
}

static void dump_word(int i, BYTE *w)
{
    static const int ints[] = {0x84, 0x88, 0x180, 0x210, 0x214, 0x228, 0x22c, 0x230, 0x234, 0x238, 0x23c, 0x240, 0x244, 0x248,
                               0x24c, 0x250, 0x254, 0x258, 0x25c, 0x260, 0x264, 0x268, 0x26c, 0x270, 0x274, 0x278, 0x27c,
                               0x2b8, 0x2bc, 0x2f0, 0x368, 0x36c};
    unsigned k;
    BYTE *fs;
    fprintf(g_out, "W %d t=", i); pstr(tstr(w, 0x98));
    fprintf(g_out, " lang=%x pos=%d tpos=%d", U16(w, 0x80), (short)U16(w, 0x138), (short)U16(w, 0x13a));
    for (k = 0; k < sizeof ints / sizeof *ints; k++) fprintf(g_out, " i%x=%d", ints[k], I32(w, ints[k]));
    fprintf(g_out, " pron="); pstr(tstr(w, 0x160));
    fprintf(g_out, " bm="); pstr(tstr(w, 0x2f8)); fprintf(g_out, " bm318=%llx", (unsigned long long)P(w, 0x318));
    fprintf(g_out, " g2e8=%llx a2b0=%d p1a8=%llx", (unsigned long long)P(w, 0x2e8), idx_of(g_w, g_nw, P(w, 0x2b0)),
            (unsigned long long)P(w, 0x1a8));
    { /* current pronunciation ids: +0x360 CTTSPronunciationList {vt, head link*, ...,+0x38 cur link}; link+0x10 -> pron, pron+0x10 -> u16 ids */
        BYTE *pl = P(w, 0x360);
        fprintf(g_out, " prid=");
        __try {
            if (pl && P(pl, 0x38)) {
                BYTE *pr = P(P(pl, 0x38), 0x10);
                const unsigned short *ids = pr ? *(const unsigned short **)(pr + 0x10) : NULL;
                int k;
                if (ids) for (k = 0; ids[k] && k < 400; k++) fprintf(g_out, "%s%d", k ? "." : "", ids[k]); else fputs("-", g_out);
            } else fputs("none", g_out);
        } __except (1) { fputs("EXC", g_out); }
    }
    fprintf(g_out, " ne="); pstr(tstr(w, 0x188));
    fprintf(g_out, " s1b0="); pstr(tstr(w, 0x1b0));
    fprintf(g_out, " s1d0="); pstr(tstr(w, 0x1d0));
    fprintf(g_out, " s1f0="); pstr(tstr(w, 0x1f0));
    fprintf(g_out, " ph=%d", idx_of(g_ph, g_nph, P(w, 0x10)));
    fprintf(g_out, " pw=%d", idx_of(g_pw, g_npw, P(w, 0x2c0)));
    fprintf(g_out, " s=%d-%d", idx_of(g_s, g_ns, P(w, 0x18)), idx_of(g_s, g_ns, P(w, 0x20)));
    fs = P(w, 0x90);
    if (fs) {
        fprintf(g_out, " fs=%p:", fs);
        __try { for (k = 0; k < 0x18; k++) fprintf(g_out, "%s%x", k ? "," : "", I32(fs, 4 * k)); } __except (1) { fputs("EXC", g_out); }
        __try { /* +0x28 prosody block (floats +0x08 middle, +0x28 rate, +0x3c volume), +0x20 say-as {InterpretAs,..} */
            BYTE *pr = P(fs, 0x28), *sa = P(fs, 0x20);
            if (pr) fprintf(g_out, " fpr=%g,%g,%g", *(float *)(pr + 8), *(float *)(pr + 0x28), *(float *)(pr + 0x3c));
            if (sa) { fprintf(g_out, " fsa="); pstr(*(wchar_t **)sa); }
        } __except (1) { fputs(" fprEXC", g_out); }
    }
    if (g_feats) { fprintf(g_out, " |"); dump_feats(w + 0x38, 8); }
    fputc('\n', g_out);
}

static void dump_tree(BYTE *utt, const char *stage)
{
    BYTE *sent = P(utt, 0xe0);
    int i;
    fprintf(g_out, "STAGE %s\n", stage);
    if (!sent) { fprintf(g_out, "NOSENT\n"); return; }
    g_nw = collect(sent, 0x28, g_w); g_ns = collect(sent, 0x38, g_s); g_np = collect(sent, 0x40, g_p);
    g_npw = collect(sent, 0x30, g_pw); g_nph = collect(sent, 0x48, g_ph); g_nip = collect(sent, 0x58, g_ip);
    fprintf(g_out, "SENT type=%d emo=%d a0=%d a4=%d off=%d len=%d dom=", I32(sent, 0xa8), I32(sent, 0xac), I32(sent, 0xa0),
            I32(sent, 0xa4), I32(sent, 0x80), I32(sent, 0x88));
    pstr(tstr(utt, 0x70));
    fprintf(g_out, " nw=%d ns=%d np=%d npw=%d nph=%d nip=%d", g_nw, g_ns, g_np, g_npw, g_nph, g_nip);
    if (g_feats) { fprintf(g_out, " |"); dump_feats(sent + 8, 0x200); }
    fputc('\n', g_out);
    for (i = 0; i < g_nw; i++) dump_word(i, g_w[i]);
    for (i = 0; i < g_ns; i++) {
        BYTE *s = g_s[i];
        fprintf(g_out, "Y %d w=%d ph=%d-%d c0=%d", i, idx_of(g_w, g_nw, P(s, 8)), idx_of(g_p, g_np, P(s, 0x10)),
                idx_of(g_p, g_np, P(s, 0x18)), I32(s, 0xc0));
        fprintf(g_out, " s80="); pstr(tstr(s, 0x80));
        fprintf(g_out, " sa0="); pstr(tstr(s, 0xa0));
        if (g_feats) { fprintf(g_out, " |"); dump_feats(s + 0x30, 4); }
        fputc('\n', g_out);
    }
    for (i = 0; i < g_np; i++) {
        BYTE *p = g_p[i];
        fprintf(g_out, "H %d s=%d id=%d st=%d a0=%d cc=%d n=", i, idx_of(g_s, g_ns, P(p, 8)), U16(p, 0x84), (short)U16(p, 0x80),
                I32(p, 0xa0), I32(p, 0xcc));
        pstr(tstr(p, 0x88));
        __try { BYTE *b = P(p, 0x78); if (b) { int k; fprintf(g_out, " ctl="); for (k = 0; k < 8; k++) fprintf(g_out, "%s%x", k ? "," : "", I32(b, 4 * k)); } }
        __except (1) { fputs(" ctlEXC", g_out); }
        if (g_feats) { fprintf(g_out, " |"); dump_feats(p + 0x30, 1); }
        fputc('\n', g_out);
    }
    for (i = 0; i < g_npw; i++) {
        BYTE *n = g_pw[i];
        fprintf(g_out, "PW %d %d %d par=%d", i, idx_of(g_w, g_nw, P(n, 0x10)), idx_of(g_w, g_nw, P(n, 0x18)), idx_of(g_ph, g_nph, P(n, 8)));
        if (g_feats) { fprintf(g_out, " |"); dump_feats(n + 0x30, 0x10); }
        fputc('\n', g_out);
    }
    for (i = 0; i < g_nph; i++) {
        BYTE *n = g_ph[i];
        fprintf(g_out, "PH %d %d %d par=%d", i, idx_of(g_w, g_nw, P(n, 0x10)), idx_of(g_w, g_nw, P(n, 0x18)), idx_of(g_ip, g_nip, P(n, 8)));
        if (g_feats) { fprintf(g_out, " |"); dump_feats(n + 0x30, 0x40); }
        fputc('\n', g_out);
    }
    for (i = 0; i < g_nip; i++) {
        BYTE *n = g_ip[i];
        fprintf(g_out, "IP %d %d %d f78=%d", i, idx_of(g_ph, g_nph, P(n, 0x10)), idx_of(g_ph, g_nph, P(n, 0x18)), I32(n, 0x78));
        if (g_feats) { fprintf(g_out, " |"); dump_feats(n + 0x30, 0x80); }
        fputc('\n', g_out);
    }
    { /* quote pairs: sentence vt+0x50 -> list of {open word, ?, close word, idx} */
        void **lst = get_list(sent, 0x50);
        Link *l;
        if (lst) for (l = (Link *)lst[0]; l; l = l->next) {
            BYTE *it = l->item;
            fprintf(g_out, "QP %d %d %d\n", idx_of(g_w, g_nw, P(it, 0)), idx_of(g_w, g_nw, P(it, 0x10)), I32(it, 0x18));
        }
    }
    { /* parallel structs: sentence vt+0x60 -> list of CParallelStruct {vt; list{head,tail,..,count}} of {a, b, int} */
        void **lst = get_list(sent, 0x60);
        Link *l; int k = 0;
        if (lst) for (l = (Link *)lst[0]; l; l = l->next, k++) {
            BYTE *ps = l->item;
            Link *e;
            fprintf(g_out, "PS %d n=%lld:", k, *(long long *)(ps + 0x18));
            for (e = *(Link **)(ps + 8); e; e = e->next) {
                BYTE *el = (BYTE *)e->item;
                fprintf(g_out, " %d,%d,%d", idx_of(g_w, g_nw, P(el, 0)), idx_of(g_w, g_nw, P(el, 8)), I32(el, 0x10));
            }
            fputc('\n', g_out);
        }
    }
    fflush(g_out);
}

static void dump_prosody_words(BYTE *utt, const char *stage)
{
    BYTE *sent = P(utt, 0xe0);
    int i;
    if (!sent) return;
    g_nw = collect(sent, 0x28, g_w);
    fprintf(g_out, "STAGE %s\n", stage);
    for (i = 0; i < g_nw; i++) {
        BYTE *w = g_w[i];
        fprintf(g_out, "B %d bi=%d/%d pc=%d em=%d/%d tone=%d/%d p228=%d p22c=%d p230=%d p240=%d p248=%d\n", i, I32(w, 0x244),
                I32(w, 0x24c), I32(w, 0x250), I32(w, 0x254), I32(w, 0x258), I32(w, 0x238), I32(w, 0x23c), I32(w, 0x228),
                I32(w, 0x22c), I32(w, 0x230), I32(w, 0x240), I32(w, 0x248));
    }
}

typedef struct Obs { void **vt; } Obs;
static int __cdecl obs_cb(Obs *self, unsigned id, int phase, BYTE *utt)
{
    (void)self;
    __try {
        if (id == 0x80000 && phase == 0) {
            fprintf(g_out, "U %d\n", g_utt++);
            dump_tree(utt, "IN");
            if (g_pred) { /* install sub-predictor observer: CLinguisticProsodyTagger = engine+0x1f8, callback at +0x30 */
                BYTE *tg = P(g_eng, 0x1f8);
                extern Obs g_pobs;
                if (tg) *(Obs **)(tg + 0x30) = &g_pobs;
                if (tg) { /* model runners: predictor +0x18 -> runner; runner +0x28 */
                    int k; static const int po[4] = {0x68, 0xb8, 0xe8, 0x118};
                    fprintf(g_out, "RUNNERS locbase=%p", (void *)GetModuleHandleW(L"MSTTSLoc_OneCore.dll"));
                    for (k = 0; k < 4; k++) {
                        BYTE *pr = tg + po[k], *rn = P(pr, 0x18), *sq = rn ? P(rn, 0x28) : NULL;
                        fprintf(g_out, " [%d r=%p sq=%p", k, rn, sq);
                        if (rn) { int o; for (o = 0; o < 0x48; o += 8) fprintf(g_out, " %llx", *(unsigned long long *)(rn + o)); }
                        if (sq) {
                            long long c = *(long long *)(sq + 0x10), q;
                            fprintf(g_out, " sqcnt=%lld", c);
                            for (q = 0; q < c && q < 4; q++) {
                                BYTE *h = ((BYTE **)P(sq, 8))[q];
                                fprintf(g_out, " h%lld=%p vt=%p", q, h, h ? P(h, 0) : NULL);
                                if (h) { int o; for (o = 8; o < 0x40; o += 8) fprintf(g_out, " %llx", *(unsigned long long *)(h + o)); }
                            }
                        }
                        fprintf(g_out, "]");
                    }
                    fputc('\n', g_out);
                    { /* break predictor say-as list (+0x30 array of 0x20-byte CTTSString, count +0x38) */
                        BYTE *bp = tg + 0x68, *arr = P(bp, 0x30);
                        long long n = *(long long *)(bp + 0x38), q;
                        fprintf(g_out, "SAYASLIST n=%lld:", n);
                        for (q = 0; arr && q < n && q < 64; q++) { fputc(' ', g_out); pstr(*(wchar_t **)(arr + 0x20 * q + 8)); }
                        fputc('\n', g_out);
                    }
                    { int kk; static const int po2[4] = {0x68, 0xb8, 0xe8, 0x118};
                      fprintf(g_out, "PRED20"); for (kk = 0; kk < 4; kk++) fprintf(g_out, " %d", I32(tg + po2[kk], 0x20)); fputc('\n', g_out); }
                }
            }
        }
        if (id == 0x100000 && phase == 0) { /* phone-converter table of the SAPI event handler (unit generator+0xc0, +8) */
            static int done;
            BYTE *ug = P(g_eng, 0x218), *cv = ug ? P(ug + 0xc0, 8) : NULL;
            if (cv && !done) {
                const unsigned short *t = *(const unsigned short **)(cv + 8);
                unsigned n = *(unsigned *)(cv + 0x10), r, c;
                done = 1;
                fprintf(g_out, "PHCONV n=%u flag10=%d\n", n, I32(ug + 0xc0, 0x10));
                for (r = 0; t && r < n; r++) {
                    fprintf(g_out, "PC");
                    for (c = 0; c < 13; c++) fprintf(g_out, " %u", t[13 * r + c]);
                    fputc('\n', g_out);
                }
            }
        }
        if (id == 0x80000 && phase == 1) dump_tree(utt, "PRO");
        if (id == 0x100000 && phase == 1) dump_tree(utt, "UNIT");
    } __except (EXCEPTION_EXECUTE_HANDLER) { fprintf(g_out, "\nEXC in dump\n"); }
    fflush(g_out);
    if (g_nowave && phase == 0 && id != 0x40000 && id != 0x80000 && id != 0x100000 && id != 0x4000000) return 1;
    return 0;
}
static int __cdecl pobs_cb(Obs *self, unsigned id, int phase, BYTE *utt)
{
    char nm[32];
    (void)self;
    sprintf(nm, "PRED%u%s", id, phase ? "a" : "b");
    __try { dump_prosody_words(utt, nm); } __except (1) { fprintf(g_out, "EXC pred\n"); }
    return 0;
}
static void *g_obs_vt[1] = {(void *)obs_cb};
static Obs g_obs = {g_obs_vt};
static void *g_pobs_vt[1] = {(void *)pobs_cb};
Obs g_pobs = {g_pobs_vt};

typedef HRESULT(STDMETHODCALLTYPE *SpeakFn)(void *, DWORD, REFGUID, const WAVEFORMATEX *, const void *, void *);
static SpeakFn g_orig_speak;
static HRESULT STDMETHODCALLTYPE my_speak(void *self, DWORD flags, REFGUID fmt, const WAVEFORMATEX *wfx, const void *frags,
                                          void *site)
{
    BYTE *eng = *(BYTE **)((BYTE *)self + OFF_ENGINE_FROM_ITTS);
    g_eng = eng;
    if (eng) *(Obs **)(eng + OFF_STAGE_OBS) = &g_obs;
    return g_orig_speak(self, flags, fmt, wfx, frags, site);
}

typedef long (*Fx_t)(void *, void *, BYTE *, BYTE *, int);
static Fx_t o_fx;
static long h_fx(void *self, void *utt, BYTE *metas, BYTE *out, int n)
{
    long hr = o_fx(self, utt, metas, out, n);
    int i;
    size_t j;
    fprintf(g_out, "FX %d hr=%08lx\n", n, hr);
    for (i = 0; i < n; i++) {
        BYTE *rec = out + 0x20 * i, *data = *(BYTE **)rec;
        size_t cnt = *(size_t *)(rec + 8);
        fprintf(g_out, "F %d prop=%d cnt=%zu:", i, *(int *)(metas + 0x100 * i + 0x68), cnt);
        for (j = 0; j < cnt; j++) {
            int kind = *(int *)(data + 16 * j);
            if (kind == 2) { fputs(" s:", g_out); pstr(*(wchar_t **)(data + 16 * j + 8)); }
            else if (kind == -1) fprintf(g_out, " N");
            else fprintf(g_out, " %d:%d", kind, *(int *)(data + 16 * j + 8));
        }
        fputc('\n', g_out);
    }
    fflush(g_out);
    return hr;
}

static void patch(void **slot, void *fn, void **orig)
{
    DWORD old;
    *orig = *slot;
    VirtualProtect(slot, 8, PAGE_READWRITE, &old);
    *slot = fn;
    VirtualProtect(slot, 8, old, &old);
}

static wchar_t *read_file(const wchar_t *path)
{
    FILE *f = _wfopen(path, L"rb");
    long n; char *b; int off, wn; wchar_t *w;
    if (!f) return NULL;
    fseek(f, 0, SEEK_END); n = ftell(f); fseek(f, 0, SEEK_SET);
    b = malloc(n + 1); fread(b, 1, n, f); b[n] = 0; fclose(f);
    off = (n >= 3 && (BYTE)b[0] == 0xEF && (BYTE)b[1] == 0xBB && (BYTE)b[2] == 0xBF) ? 3 : 0;
    wn = MultiByteToWideChar(CP_UTF8, 0, b + off, -1, NULL, 0);
    w = malloc(wn * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, b + off, -1, w, wn);
    free(b);
    return w;
}

int wmain(int argc, wchar_t **argv)
{
    ISpObjectToken *tok = NULL; ISpVoice *v = NULL; ISpStream *st = NULL; IStream *mem = NULL;
    wchar_t tokid[512], *text, *line, *next;
    const wchar_t *tn;
    HRESULT hr;
    WAVEFORMATEX wf = {WAVE_FORMAT_PCM, 1, 16000, 32000, 2, 16, 0};
    ULONGLONG interest;
    int ln = 0, i;
    if (argc < 4) { fwprintf(stderr, L"usage: zftap2 david|zira|mark @corpus.txt out.txt [nowave] [feats] [pred]\n"); return 1; }
    tn = !_wcsicmp(argv[1], L"zira") ? L"MSTTS_V110_enUS_ZiraM" : !_wcsicmp(argv[1], L"mark") ? L"MSTTS_V110_enUS_MarkM" : L"MSTTS_V110_enUS_DavidM";
    swprintf(tokid, 512, L"%ls%ls", TOKROOT, tn);
    text = argv[2][0] == L'@' ? read_file(argv[2] + 1) : _wcsdup(argv[2]);
    if (!text) { fwprintf(stderr, L"cannot read corpus\n"); return 1; }
    g_out = _wfopen(argv[3], L"wb");
    for (i = 4; i < argc; i++) {
        if (!wcscmp(argv[i], L"nowave")) g_nowave = 1;
        if (!wcscmp(argv[i], L"feats")) g_feats = 1;
        if (!wcscmp(argv[i], L"pred")) g_pred = 1;
    }
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    g_base = (BYTE *)LoadLibraryW(ENGINE_DLL);
    if (!g_base) return 1;
    {
        void **slot = (void **)(g_base + RVA_VT_TTSENG + 3 * 8);
        if (*slot != g_base + RVA_SPEAK) { fwprintf(stderr, L"engine mismatch\n"); return 2; }
        patch(slot, (void *)my_speak, (void **)&g_orig_speak);
    }
    patch((void **)(g_base + 0x1714b8) + 3, (void *)h_fx, (void **)&o_fx);
    hr = CoCreateInstance(&CLSID_SpObjectToken, NULL, CLSCTX_ALL, &IID_ISpObjectToken, (void **)&tok);
    if (SUCCEEDED(hr)) hr = ISpObjectToken_SetId(tok, NULL, tokid, FALSE);
    if (SUCCEEDED(hr)) hr = CoCreateInstance(&CLSID_SpVoice, NULL, CLSCTX_ALL, &IID_ISpVoice, (void **)&v);
    if (SUCCEEDED(hr)) hr = ISpVoice_SetVoice(v, tok);
    if (FAILED(hr)) { fwprintf(stderr, L"voice setup failed %08lx\n", hr); return 1; }
    CreateStreamOnHGlobal(NULL, TRUE, &mem);
    CoCreateInstance(&CLSID_SpStream, NULL, CLSCTX_ALL, &IID_ISpStream, (void **)&st);
    hr = ISpStream_SetBaseStream(st, mem, &SPDFID_WaveFormatEx, &wf);
    if (SUCCEEDED(hr)) hr = ISpVoice_SetOutput(v, (IUnknown *)st, TRUE);
    interest = SPFEI(SPEI_WORD_BOUNDARY) | SPFEI(SPEI_SENTENCE_BOUNDARY) | SPFEI(SPEI_PHONEME) | SPFEI(SPEI_VISEME) |
               SPFEI(SPEI_TTS_BOOKMARK);
    ISpVoice_SetInterest(v, interest, interest);
    for (line = text; line && *line; line = next) {
        SPEVENT ev; ULONG got;
        next = wcschr(line, L'\n');
        if (next) *next++ = 0;
        if (*line && line[wcslen(line) - 1] == L'\r') line[wcslen(line) - 1] = 0;
        ln++;
        if (!*line || (line[0] == L'#' && line[1] == L'#')) continue;
        fprintf(g_out, "LINE %d ", ln); pstr(line); fputc('\n', g_out);
        g_utt = 0;
        hr = ISpVoice_Speak(v, line, wcschr(line, L'<') ? SPF_IS_XML : SPF_IS_NOT_XML, NULL);
        fprintf(g_out, "SPEAKHR %08lx\n", hr);
        while (ISpVoice_GetEvents(v, 1, &ev, &got) == S_OK && got == 1) {
            fprintf(g_out, "EV %u %llu %lld %llu", ev.eEventId, (ULONGLONG)ev.wParam,
                    (LONGLONG)(ev.elParamType == SPET_LPARAM_IS_UNDEFINED ? ev.lParam : 0), ev.ullAudioStreamOffset);
            if (ev.elParamType == SPET_LPARAM_IS_STRING) { fputc(' ', g_out); pstr((wchar_t *)ev.lParam); }
            fputc('\n', g_out);
            if (ev.elParamType == SPET_LPARAM_IS_STRING || ev.elParamType == SPET_LPARAM_IS_POINTER) CoTaskMemFree((void *)ev.lParam);
        }
        fflush(g_out);
    }
    fclose(g_out);
    return 0;
}
