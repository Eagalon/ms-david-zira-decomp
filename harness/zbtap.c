/* zbtap: x64 tap of the OneCore HTS acoustic backend (MSTTSEngine_OneCore.dll 10.3.21207) for the C port (src/zb_*).
 * Speaks text via SAPI5 with a OneCore voice token and writes a tagged binary log (the golden file for zb_backtest):
 *   record = char tag[4]; u32 nbytes; payload
 *   'HDR ' u32 version=1, i32 siteRate, u32 siteVolume, u32 isInt(voice), wchar voicePath...   (once)
 *   'UTT ' u32 index, i32 intFlag(utt+0x2c0)                                   (per sentence, at backend entry)
 *   'FEAT' u32 nfeat, u32 nphone, then nfeat*nphone cells {i32 kind, i32 value} (feature-major; kind -1 = null,
 *          kind 2 = string, value = index into the following 'FSTR' record)       (feature matrix, 0x18005bfc0)
 *   'FSTR' u32 n; n x {u32 nchars; u16 chars[nchars]}
 *   'PHON' u32 nphone, then per phone ZbTapPhone (see struct below)            (phone list of the acoustic space)
 *   'DUR ' u32 rows, cols; u32 d[rows*cols]                                     (state durations after CDurationPredictor)
 *   'VUV ' u32 1, T; i32 v[T]                                                   (after CUVPredictor)
 *   'LF0 ' / 'LSF ' / 'GAIN' u32 rows, cols; f32|i32 data[]                     (after each stream predictor)
 *   'FIN ' u32 rows,cols F0; data; u32 rows,cols LSF; data; u32 rows,cols gain; data   (at CWaveGenerator::Begin)
 *   'PCM ' i16 samples[]                                                        (every CTTSEngineSite::Write)
 *   'PHX '  u32 nphone, per phone i32 {segment+0x4c stretch flag, segment+0x40, segment+0x3c}
 *   'SSPD'  f32 Sonic speed (CRateChangerSonic::SetSpeed)
 *   'SPRC'  i32 nin, flags, nout; i16 in[nin]; i16 out[nout] (CRateChangerSonic::Process; flags 2 = flush)
 *   'UEND'                                                                      (end-of-utterance vocoder reset)
 * Build: build_zbtap.bat.   Usage: zbtap.exe "text" out.wav log.bin [token] [rate] [volume]
 */
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#include <windows.h>
#include <sapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENGINE L"C:/Windows/System32/speech_onecore/engines/tts/MSTTSEngine_OneCore.dll"
#define DAVID L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices\\Tokens\\MSTTS_V110_enUS_DavidM"
#define RVA(va) ((ULONG_PTR)(va) - 0x180000000ULL)

static BYTE *g_eng, *g_tramp;
static int g_ntramp, g_utt, g_verbose;
static FILE *g_log;
typedef struct { unsigned rows, cols; void *data; } Mat;

static void rec(const char *tag, const void *a, size_t na, const void *b, size_t nb)
{
    unsigned n = (unsigned)(na + nb);
    fwrite(tag, 1, 4, g_log);
    fwrite(&n, 4, 1, g_log);
    if (na) fwrite(a, 1, na, g_log);
    if (nb) fwrite(b, 1, nb, g_log);
}
static void recmat(const char *tag, Mat *m)
{
    unsigned h[2] = {0, 0};
    if (m) { h[0] = m->rows; h[1] = m->cols; }
    rec(tag, h, 8, m ? m->data : 0, m && m->data ? (size_t)m->rows * m->cols * 4 : 0);
}

static void patch(void **slot, void *fn, void **orig)
{
    DWORD old;
    *orig = *slot;
    VirtualProtect(slot, 8, PAGE_READWRITE, &old);
    *slot = fn;
    VirtualProtect(slot, 8, old, &old);
}
static void *redirect(ULONG_PTR va, void *fn)
{
    BYTE *site = g_eng + RVA(va), *stub = g_tramp + 16 * g_ntramp++;
    DWORD old;
    void *orig;
    if (site[0] != 0xE8) { printf("site %llx is not a call\n", (unsigned long long)va); exit(1); }
    orig = site + 5 + *(int *)(site + 1);
    stub[0] = 0x48; stub[1] = 0xB8; *(void **)(stub + 2) = fn; stub[10] = 0xFF; stub[11] = 0xE0;
    VirtualProtect(site, 5, PAGE_EXECUTE_READWRITE, &old);
    *(int *)(site + 1) = (int)(stub - (site + 5));
    VirtualProtect(site, 5, old, &old);
    return orig;
}

static BYTE *space_of(BYTE *utt) { return utt + (*(int *)(utt + 0x2c0) ? 0x4d0 : 0x2c8); }

/* ---- engine helpers called directly ---- */
typedef long long (*P1_t)(void *);
typedef void *(*Nav_t)(void *, int);
#define EFN(t, va) ((t)(g_eng + RVA(va)))

#pragma pack(push, 1)
typedef struct {
    unsigned short id;        /* phone+0x84 */
    unsigned short pad;
    int isPauseLike;          /* FUN_18004d844 */
    int isSil;                /* FUN_18001d540 */
    int wordIndex;            /* index of the owning word (FUN_180049120) in order of appearance, -1 none */
    int wordType;             /* word vt+0x1b0 */
    int word90;               /* *(int*)(word+0x90) or -1 */
    int skip;                 /* phone vt+8 */
    int ctl[16];              /* phone+0x78 -> 16 dwords (prosody block: volume, rate, pitch, f32 range, ...) */
} ZbTapPhone;
#pragma pack(pop)

static void dump_phones(BYTE *utt)
{
    BYTE *sp = space_of(utt), **lst = *(BYTE ***)(sp + 0x80), *ph = NULL;
    ZbTapPhone *arr;
    void *words[4096];
    int nw = 0;
    unsigned n = 0, cap = 4096;
    if (lst && lst[2]) ph = *(BYTE **)((BYTE *)lst[0] + 0x10);
    arr = (ZbTapPhone *)calloc(cap, sizeof *arr);
    for (; ph && n < cap; ph = (BYTE *)EFN(Nav_t, 0x180035600)(ph, 0), n++) {
        ZbTapPhone *p = &arr[n];
        BYTE *w, *blk;
        int k;
        p->id = *(unsigned short *)(ph + 0x84);
        p->isPauseLike = (int)EFN(P1_t, 0x18004d844)(ph);
        p->isSil = (int)(EFN(P1_t, 0x18001d540)(ph) & 0xff);
        p->skip = (int)(*(long long (**)(void *))(*(BYTE **)ph + 8))(ph);
        w = (BYTE *)EFN(P1_t, 0x180049120)(ph);
        p->wordIndex = -1; p->wordType = -1; p->word90 = -1;
        if (w) {
            for (k = 0; k < nw && words[k] != w; k++);
            if (k == nw && nw < 4096) words[nw++] = w;
            p->wordIndex = k;
            p->wordType = (int)(*(long long (**)(void *))(*(BYTE **)w + 0x1b0))(w);
            if (*(int **)(w + 0x90)) p->word90 = **(int **)(w + 0x90);
        }
        blk = *(BYTE **)(ph + 0x78);
        if (blk) memcpy(p->ctl, blk, sizeof p->ctl);
    }
    rec("PHON", &n, 4, arr, n * sizeof *arr);
    free(arr);
    { /* 'PHX ' per phone: segment (phone+0xd8) +0x4c (waveform time-stretch flag), +0x40, +0x3c */
        int *x = (int *)calloc((size_t)n * 3 + 1, 4);
        unsigned k = 0;
        ph = (lst && lst[2]) ? *(BYTE **)((BYTE *)lst[0] + 0x10) : NULL;
        for (; ph && k < n; ph = (BYTE *)EFN(Nav_t, 0x180035600)(ph, 0), k++) {
            BYTE *seg = *(BYTE **)(ph + 0xd8);
            if (seg) { x[3 * k] = *(int *)(seg + 0x4c); x[3 * k + 1] = *(int *)(seg + 0x40); x[3 * k + 2] = *(int *)(seg + 0x3c); }
            else x[3 * k] = x[3 * k + 1] = x[3 * k + 2] = -99;
        }
        rec("PHX ", &n, 4, x, (size_t)n * 12);
        free(x);
    }
    { /* 'PDOM' per phone: i32 word90 (*(int*)(word+0x90), 1 = no rate adjustments), i32 nchars, u16 domain name[]
       * of the segment's word (FUN_18005418c(segment) -> vt+0xe0; e.g. "phoneNumber"; "none" = no domain) */
        BYTE *buf = (BYTE *)malloc(64 * 1024), *o = buf;
        unsigned k = 0;
        ph = (lst && lst[2]) ? *(BYTE **)((BYTE *)lst[0] + 0x10) : NULL;
        memcpy(o, &n, 4); o += 4;
        for (; ph && k < n && o < buf + 60 * 1024; ph = (BYTE *)EFN(Nav_t, 0x180035600)(ph, 0), k++) {
            BYTE *seg = *(BYTE **)(ph + 0xd8), *w = seg ? (BYTE *)EFN(P1_t, 0x18005418c)(seg) : NULL;
            int w90 = -1, len = 0;
            const wchar_t *nm = NULL;
            if (w) {
                BYTE sobj[64];
                BYTE *r;
                memset(sobj, 0, sizeof sobj);
                if (*(int **)(w + 0x90)) w90 = **(int **)(w + 0x90);
                r = (BYTE *)(*(void *(**)(void *, void *))(*(BYTE **)w + 0xe0))(w, sobj);
                if (r) nm = *(const wchar_t **)(r + 8);
                if (nm) len = (int)wcslen(nm);
                if (len > 64) len = 64;
            }
            memcpy(o, &w90, 4); o += 4;
            memcpy(o, &len, 4); o += 4;
            if (len) { memcpy(o, nm, 2 * (size_t)len); o += 2 * len; }
        }
        rec("PDOM", buf, (size_t)(o - buf), 0, 0);
        free(buf);
    }
}

/* ---- feature extractor vtable 0x1801714b8 slot 3 ---- */
typedef long (*Fx_t)(void *, void *, BYTE *, BYTE *, int);
static Fx_t o_fx;
static long h_fx(void *self, void *utt, BYTE *metas, BYTE *out, int n)
{
    long hr = o_fx(self, utt, metas, out, n);
    int i;
    size_t j, np;
    if (n > 1) {
        int *cells;
        unsigned hdr[2], nstr = 0;
        wchar_t *strs[8192];
        np = *(size_t *)(out + 8);
        hdr[0] = n; hdr[1] = (unsigned)np;
        cells = (int *)malloc((size_t)n * np * 8);
        for (i = 0; i < n; i++) {
            BYTE *data = *(BYTE **)(out + 0x20 * i);
            if (*(size_t *)(out + 0x20 * i + 8) != np) printf("FEAT: feature %d count %zu != %zu\n", i, *(size_t *)(out + 0x20 * i + 8), np);
            for (j = 0; j < np; j++) {
                int kind = *(int *)(data + 16 * j);
                cells[2 * (i * np + j)] = kind;
                if (kind == 2) {
                    strs[nstr] = *(wchar_t **)(data + 16 * j + 8);
                    cells[2 * (i * np + j) + 1] = nstr < 8191 ? nstr++ : nstr;
                } else
                    cells[2 * (i * np + j) + 1] = *(int *)(data + 16 * j + 8);
            }
        }
        rec("FEAT", hdr, 8, cells, (size_t)n * np * 8);
        free(cells);
        {
            unsigned k, tot = 4;
            for (k = 0; k < nstr; k++) tot += 4 + 2 * (unsigned)(strs[k] ? wcslen(strs[k]) : 0);
            fwrite("FSTR", 1, 4, g_log); fwrite(&tot, 4, 1, g_log); fwrite(&nstr, 4, 1, g_log);
            for (k = 0; k < nstr; k++) {
                unsigned l = (unsigned)(strs[k] ? wcslen(strs[k]) : 0);
                fwrite(&l, 4, 1, g_log);
                if (l) fwrite(strs[k], 2, l, g_log);
            }
        }
        if (g_verbose) printf("FEAT n=%d phones=%zu strings=%u\n", n, np, nstr);
    }
    return hr;
}

/* ---- stage callback installed at CAcousticProsodyTagger+0x30 ---- */
typedef long (*Cb_t)(void *, unsigned, int, void *);
static void *g_prevcb;
static long cb_fn(void *self, unsigned mask, int phase, BYTE *utt);
static void *g_cbvt[4] = {(void *)cb_fn, 0, 0, 0};
static void *g_cbobj[2] = {g_cbvt, 0};
static long cb_fn(void *self, unsigned mask, int phase, BYTE *utt)
{
    BYTE *sp = space_of(utt);
    long hr = 0;
    (void)self;
    if (g_prevcb) hr = (*(Cb_t *)*(void **)g_prevcb)(g_prevcb, mask, phase, utt);
    if (g_verbose) printf("  stage %08x %s\n", mask, phase ? "after" : "before");
    if (mask == 0x4000010 && phase == 0) {
        dump_phones(utt);
        recmat("DUR ", *(Mat **)(sp + 8));
        if (*(int *)(utt + 0x2c0) && getenv("ZBTAP_INTREFS")) {   /* debug: int-space F0 model refs (space+0x188) */
            BYTE *arr = *(BYTE **)(sp + 0x188);
            unsigned n = *(unsigned *)(sp + 0xb0) * *(unsigned *)(sp + 0xb4), k;
            size_t cnt = *(size_t *)(sp + 0x190);
            printf("space+0x188=%p +0x190=%zu +0x198=%zu n=%u\n", arr, cnt, *(size_t *)(sp + 0x198), n);
            for (k = 0; arr && k < n; k++) {
                BYTE *e = arr + 0x18 * k;
                short *m = *(short **)e;
                printf("  e%u: w=%d m=%d,%d,%d\n", k, *(short *)(e + 0x10), m ? m[0] : 0, m ? m[1] : 0, m ? m[2] : 0);
            }
        }
    }
    if (mask == 0x4000010 && phase == 1) {
        Mat vm = **(Mat **)(sp + 0x10);   /* {?, T, int *flags}: first dword is not a row count */
        vm.rows = 1;
        recmat("VUV ", &vm);
    }
    if (mask == 0x4000040 && phase == 0) {
        /* 'QIAN' question-intonation anchor as the engine computes it (FUN_1800a5b70 int / FUN_1800a5cbc float, run on
         * the not yet generated F0 = all zero, so only the return code and the per-word sentence types matter here);
         * i32 ret, frame, then per phone: *(int*)(word+0x228) (sentence type seen by QuestionIntonation) */
        BYTE **lst = *(BYTE ***)(sp + 0x80), *ph = NULL;
        int buf[4098], n = 0;
        if (lst && lst[2]) ph = *(BYTE **)((BYTE *)lst[0] + 0x10);
        for (; ph && n < 4096; ph = (BYTE *)EFN(Nav_t, 0x180035600)(ph, 0), n++) {
            BYTE *w = (BYTE *)EFN(P1_t, 0x180049120)(ph);
            buf[2 + n] = w ? *(int *)(w + 0x228) : -1;
        }
        buf[0] = 0; buf[1] = -1;
        rec("QIAN", buf, 8 + 4 * (size_t)n, 0, 0);
    }
    if (mask == 0x4000040 && phase == 1) {
        recmat("LF0 ", *(Mat **)(sp + 0xc0));
        {   /* 'QIA2' i32 ret, frame: the engine's own question-intonation anchor query (FUN_1800a5b70 int /
             * FUN_1800a5cbc float) on the final F0; ret 0 = anchor found (ramp applied if QuestionIntonation is on) */
            typedef unsigned long long (*Qa_t)(void *, unsigned *);
            unsigned fr = 0xffffffff;
            int q[2];
            q[0] = (int)(*(int *)(utt + 0x2c0) ? EFN(Qa_t, 0x1800a5b70) : EFN(Qa_t, 0x1800a5cbc))(sp, &fr);
            q[1] = (int)fr;
            rec("QIA2", q, 8, 0, 0);
            if (g_verbose) {   /* replicate the anchor walk of FUN_1800a5b70 */
                BYTE **lst = *(BYTE ***)(sp + 0x80), *ph0 = lst && lst[2] ? *(BYTE **)((BYTE *)lst[0] + 0x10) : NULL, *w;
                w = ph0 ? (BYTE *)EFN(P1_t, 0x180049120)(ph0) : NULL;
                while (w) {
                    BYTE *nx = (BYTE *)EFN(Nav_t, 0x180045a04)(w + 8, 0), *lc = (BYTE *)EFN(Nav_t, 0x18005c630)(w + 8, 1);
                    printf("  qi walk: node %p +228=%d next=%p last/prev=%p", w, *(int *)(w + 0x228), nx, lc);
                    if (lc) {
                        BYTE *x = *(BYTE **)(*(BYTE **)(lc + 0x20) + 0x10);
                        printf(" -> first elem %p id=%d", x, x ? *(unsigned short *)(x + 0x84) : -1);
                    }
                    printf("\n");
                    w = nx;
                }
            }
        }
    }
    if (mask == 0x4000080 && phase == 1) recmat("LSF ", *(Mat **)(sp + 0xc8));
    if (mask == 0x4000100 && phase == 1) recmat("GAIN", *(Mat **)(sp + 0xd8));
    return hr;
}

/* ---- CAcousticProsodyTagger::Process (vtbl 0x18016ea58 slot 3) ---- */
typedef long (*Proc_t)(void *, void *, void *, void *);
static Proc_t o_tag;
static long h_tag(BYTE *self, BYTE *utt, void *c, void *d)
{
    int hdr[2];
    if (*(void **)(self + 0x30) != (void *)g_cbobj) {
        g_prevcb = *(void **)(self + 0x30);
        *(void **)(self + 0x30) = g_cbobj;
        if (g_verbose) printf("stage callback installed (previous %p)\n", g_prevcb);
        if (g_verbose) {   /* predictor dims (+0x18/+0x1c/+0x20) and window sets (+8 -> {?, nwin@+8, win[] @+0x10 (0x18 B)}) */
            static const int off[3] = {0x200, 0x290, 0x3a0};
            int i;
            for (i = 0; i < 3; i++) {
                BYTE *p = self + off[i], *ws = *(BYTE **)(p + 8);
                printf("pred+%x: stream=%d +18=%d +1c=%d +20=%d +78=%d nwin=%d", off[i], *(int *)(p + 0x10), *(int *)(p + 0x18),
                       *(int *)(p + 0x1c), *(int *)(p + 0x20), *(int *)(p + 0x78), ws ? *(int *)(ws + 8) : -1);
                if (ws) {
                    int w;
                    for (w = 0; w < *(int *)(ws + 8) && w < 4; w++) {
                        BYTE *we = *(BYTE **)(ws + 0x10) + 0x18 * w, *co = *(BYTE **)(we + 8);
                        int k;
                        printf(" [%d..%d:", *(int *)(we + 0x10), *(int *)(we + 0x14));
                        for (k = 0; co && k < *(int *)(co + 4); k++) printf(" %g", (*(float **)(co + 8))[k]);
                        printf("]");
                    }
                }
                printf("\n");
            }
        }
    }
    hdr[0] = g_utt++; hdr[1] = -1;
    rec("UTT ", hdr, 8, 0, 0);
    return o_tag(self, utt, c, d);
}

/* ---- CWaveGenerator stream Begin (vtbl 0x180173060 slot 6) ---- */
static Proc_t o_wbeg;
static BYTE *g_lastutt;
static long h_wbeg(void *self, BYTE *utt, void *c, void *d)
{
    BYTE *sp = space_of(utt);
    int f[2] = {0, *(int *)(utt + 0x2c0)};
    g_lastutt = utt;
    rec("INTF", f, 8, 0, 0);
    recmat("FIN0", *(Mat **)(sp + 0xc0));
    recmat("FIN1", *(Mat **)(sp + 0xc8));
    recmat("FIN2", *(Mat **)(sp + 0xd8));
    return o_wbeg(self, utt, c, d);
}

/* ---- engine output FUN_18004ba04(output, pcm, bytes) : call site in FUN_18006d71c ---- */
typedef long (*Out_t)(void *, void *, unsigned);
static Out_t o_out;
static long h_out(void *o, void *pcm, unsigned bytes)
{
    rec("PCM ", pcm, bytes, 0, 0);
    return o_out(o, pcm, bytes);
}
/* ---- CRateChangerSonic (vtbl 0x180179238): slot1 setSpeed(double), slot4 process(in, n, outbuf, outcount, flags) ---- */
typedef long (*SSpd_t)(void *, double);
typedef long (*SPrc_t)(void *, void *, int, int *, int *, int);
static SSpd_t o_sspd;
static SPrc_t o_sprc;
static long h_sspd(void *self, double sp) { float f = (float)sp; rec("SSPD", &f, 4, 0, 0); return o_sspd(self, sp); }
static long h_sprc(void *self, void *in, int n, int *ob, int *oc, int flags)
{
    long hr = o_sprc(self, in, n, ob, oc, flags);
    int h[3] = {n, flags, *oc};
    fwrite("SPRC", 1, 4, g_log);
    { unsigned tot = 12 + (in && n > 0 ? 2 * n : 0) + 2 * (*oc > 0 ? *oc : 0); fwrite(&tot, 4, 1, g_log); }
    fwrite(h, 4, 3, g_log);
    if (in && n > 0) fwrite(in, 2, n, g_log);
    if (*oc > 0) fwrite(*(short **)(ob + 2), 2, *oc, g_log);
    return hr;
}
/* ---- CRateChanger (vtbl 0x180171280, voices without WaveScale=Sonic: Zira, Mark): slot1 setSpeed(double, int *),
 * slot4 process(in, n, outvec, outcount, flags); slot5 flush calls slot4(NULL, 0, .., 2) through the vtable.
 * 'RSPD' f64 speed; 'RPRC' same layout as 'SPRC' ---- */
typedef long (*RSpd_t)(void *, double, int *);
static RSpd_t o_rspd;
static SPrc_t o_rprc;
static long h_rspd(void *self, double sp, int *o) { rec("RSPD", &sp, 8, 0, 0); return o_rspd(self, sp, o); }
static long h_rprc(void *self, void *in, int n, int *ob, int *oc, int flags)
{
    long hr = o_rprc(self, in, n, ob, oc, flags);
    int h[3] = {n, flags, *oc};
    fwrite("RPRC", 1, 4, g_log);
    { unsigned tot = 12 + (in && n > 0 ? 2 * n : 0) + 2 * (*oc > 0 ? *oc : 0); fwrite(&tot, 4, 1, g_log); }
    fwrite(h, 4, 3, g_log);
    if (in && n > 0) fwrite(in, 2, n, g_log);
    if (*oc > 0) fwrite(*(short **)(ob + 2), 2, *oc, g_log);
    return hr;
}
typedef void (*Rst_t)(void *);
static Rst_t o_rst;
/* ---- int path: LSF/gain chunk generation FUN_18010f584(vocoder, utt, startPhone, &count, &overlap), call site
 * 0x180110422 in FUN_180110394. 'LSFC' u32 start, count, overlap; then LSF and gain matrices (int) snapshots ---- */
typedef unsigned long long (*Lsfc_t)(BYTE *, BYTE *, unsigned, int *, unsigned *);
static Lsfc_t o_lsfc;
static unsigned long long h_lsfc(BYTE *voc, BYTE *utt, unsigned start, int *cnt, unsigned *ov)
{
    unsigned long long r = o_lsfc(voc, utt, start, cnt, ov);
    BYTE *sp = space_of(utt);
    if (g_verbose) {
        BYTE *ws = *(BYTE **)(voc + 0x88);
        int w, k;
        printf("vocoder LSF gen: +90=%d +94=%d +98=%d +9c=%d +f8..=%d %d %d %d %d nwin=%d", *(int *)(voc + 0x90), *(int *)(voc + 0x94),
               *(int *)(voc + 0x98), *(int *)(voc + 0x9c), *(int *)(voc + 0xf8), *(int *)(voc + 0xfc), *(int *)(voc + 0x100),
               *(int *)(voc + 0x104), *(int *)(voc + 0x108), ws ? *(int *)(ws + 8) : -1);
        for (w = 0; ws && w < *(int *)(ws + 8) && w < 4; w++) {
            BYTE *we = *(BYTE **)(ws + 0x10) + 0x18 * w, *co = *(BYTE **)(we + 8);
            printf(" [%d..%d:", *(int *)(we + 0x10), *(int *)(we + 0x14));
            for (k = 0; co && k < *(int *)(co + 4); k++) printf(" %g", (*(float **)(co + 8))[k]);
            printf("]");
        }
        printf("\n");
    }
    Mat *l = *(Mat **)(sp + 0xc8), *g = *(Mat **)(sp + 0xd8);
    unsigned h[7] = {start, (unsigned)*cnt, *ov, l ? l->rows : 0, l ? l->cols : 0, g ? g->rows : 0, g ? g->cols : 0};
    size_t nl = l ? (size_t)l->rows * l->cols * 4 : 0, ng = g ? (size_t)g->rows * g->cols * 4 : 0;
    fwrite("LSFC", 1, 4, g_log);
    { unsigned tot = (unsigned)(28 + nl + ng); fwrite(&tot, 4, 1, g_log); }
    fwrite(h, 4, 7, g_log);
    if (nl) fwrite(l->data, 1, nl, g_log);
    if (ng) fwrite(g->data, 1, ng, g_log);
    return r;
}

static void h_rst(void *v)
{
    if (g_lastutt) {   /* streams as the vocoder consumed them (int path: LSF/gain are generated in chunks during synthesis) */
        BYTE *sp = space_of(g_lastutt);
        recmat("END0", *(Mat **)(sp + 0xc0));
        recmat("END1", *(Mat **)(sp + 0xc8));
        recmat("END2", *(Mat **)(sp + 0xd8));
        g_lastutt = NULL;
    }
    o_rst(v);
    rec("UEND", 0, 0, 0, 0);
}

int wmain(int argc, wchar_t **argv)
{
    ISpVoice *voice = NULL;
    ISpObjectToken *tok = NULL;
    ISpStream *stream = NULL;
    WAVEFORMATEX wf = {WAVE_FORMAT_PCM, 1, 16000, 32000, 2, 16, 0};
    HRESULT hr;
    ULONG_PTR a;
    int rate = 0, vol = 100;
    const wchar_t *token = DAVID;
    if (argc < 4) { fwprintf(stderr, L"usage: zbtap \"text\" out.wav log.bin [token] [rate] [volume]\n"); return 1; }
    if (argc > 4 && argv[4][0]) token = argv[4];
    if (argc > 5) rate = _wtoi(argv[5]);
    if (argc > 6) vol = _wtoi(argv[6]);
    g_verbose = getenv("ZBTAP_VERBOSE") != NULL;
    setvbuf(stdout, NULL, _IONBF, 0);
    g_eng = (BYTE *)LoadLibraryW(ENGINE);
    if (!g_eng) { fprintf(stderr, "cannot load engine\n"); return 1; }
    for (a = (ULONG_PTR)g_eng - 0x10000; a > (ULONG_PTR)g_eng - 0x70000000 && !g_tramp; a -= 0x10000)
        g_tramp = (BYTE *)VirtualAlloc((void *)a, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!g_tramp) { fprintf(stderr, "no trampoline page\n"); return 1; }
    g_log = _wfopen(argv[3], L"wb");
    if (!g_log) { fprintf(stderr, "cannot open log\n"); return 1; }
    {
        int h[4] = {1, rate, vol, 0};
        rec("HDR ", h, 16, token, wcslen(token) * 2);
    }
    patch((void **)(g_eng + 0x1714b8) + 3, (void *)h_fx, (void **)&o_fx);
    patch((void **)(g_eng + 0x16ea58) + 3, (void *)h_tag, (void **)&o_tag);
    patch((void **)(g_eng + 0x173060) + 6, (void *)h_wbeg, (void **)&o_wbeg);
    patch((void **)(g_eng + 0x179238) + 1, (void *)h_sspd, (void **)&o_sspd);
    patch((void **)(g_eng + 0x179238) + 4, (void *)h_sprc, (void **)&o_sprc);
    patch((void **)(g_eng + 0x171280) + 1, (void *)h_rspd, (void **)&o_rspd);
    patch((void **)(g_eng + 0x171280) + 4, (void *)h_rprc, (void **)&o_rprc);
    o_out = (Out_t)redirect(0x18006d9c5, (void *)h_out);
    o_rst = (Rst_t)redirect(0x1800321e1, (void *)h_rst);
    o_lsfc = (Lsfc_t)redirect(0x180110422, (void *)h_lsfc);
    CoInitialize(NULL);
    hr = CoCreateInstance(&CLSID_SpVoice, NULL, CLSCTX_ALL, &IID_ISpVoice, (void **)&voice);
    if (SUCCEEDED(hr)) hr = CoCreateInstance(&CLSID_SpObjectToken, NULL, CLSCTX_ALL, &IID_ISpObjectToken, (void **)&tok);
    if (SUCCEEDED(hr)) hr = ISpObjectToken_SetId(tok, NULL, token, FALSE);
    if (SUCCEEDED(hr)) hr = ISpVoice_SetVoice(voice, tok);
    if (FAILED(hr)) { fprintf(stderr, "voice %08lx\n", hr); return 1; }
    if (rate) ISpVoice_SetRate(voice, rate);
    if (vol != 100) ISpVoice_SetVolume(voice, (USHORT)vol);
    hr = CoCreateInstance(&CLSID_SpStream, NULL, CLSCTX_ALL, &IID_ISpStream, (void **)&stream);
    if (SUCCEEDED(hr)) hr = ISpStream_BindToFile(stream, argv[2], SPFM_CREATE_ALWAYS, &SPDFID_WaveFormatEx, &wf, 0);
    if (SUCCEEDED(hr)) hr = ISpVoice_SetOutput(voice, (IUnknown *)stream, TRUE);
    if (FAILED(hr)) { fprintf(stderr, "output %08lx\n", hr); return 1; }
    hr = ISpVoice_Speak(voice, argv[1], wcschr(argv[1], L'<') ? SPF_IS_XML : SPF_DEFAULT, NULL);
    if (g_verbose || FAILED(hr)) printf("Speak hr=%08lx\n", hr);
    ISpStream_Close(stream);
    ISpStream_Release(stream);
    ISpObjectToken_Release(tok);
    ISpVoice_Release(voice);
    CoUninitialize();
    fclose(g_log);
    return 0;
}
