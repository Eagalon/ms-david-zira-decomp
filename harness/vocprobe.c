/* vocprobe: x64 probe of the OneCore SPS vocoder (MSTTSEngine_OneCore.dll 10.3.21207).
 * Speaks text via SAPI5 with the "Microsoft David Desktop" token (OneCore engine + M1033David data),
 * redirects selected rel32 CALL sites inside the engine to logging hooks (via a trampoline page
 * allocated within +-2GB of the DLL), and dumps vocoder inputs/outputs to vocdump.bin.
 * Build (x64 VS env): cl /nologo /O2 /W3 vocprobe.c ole32.lib sapi.lib
 * Usage: vocprobe.exe "text" out.wav [token-id]
 * Dump records (little endian), each: u32 tag, u32 nbytes, payload:
 *   'EXC0' simple excitation: u32 rows,cols,nsamp,shift; f32 F0[rows*cols]; f32 exc[nsamp]
 *   'EXC1' MBE excitation:    u32 rows,cols,mrows,mcols,nsamp,shift; f32 F0; f32 MBE; f32 exc[nsamp]
 *   'SYN0' synthesis: u32 rows,order,grows,gcols,nsamp,shift,itfte; f32 warp; u32 haswarp,haspower;
 *                     f32 LSF[rows*order]; f32 gain[grows*gcols]; f32 exc[nsamp]; i16 out[nsamp]
 *   'SHRP' LSF before/after LsfSharpen: u32 rows,order; f32 before[]; f32 after[]
 *   'IEX0','ISHP','ISYN': same layouts as EXC0/SHRP/SYN0 but int32 matrices/excitation (fixed-point path)
 *   'RSET' (empty) end-of-utterance reset of excitation (srand(0x406)) and synthesizer state
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
#define DAVID L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech\\Voices\\Tokens\\TTS_MS_EN-US_DAVID_11.0"
#define RVA(va) ((ULONG_PTR)(va) - 0x180000000ULL)

static BYTE *g_eng, *g_tramp;
static int g_ntramp;
static FILE *g_dump;

typedef struct { unsigned rows, cols; float *data; } Mat;

static void rec(const char *tag, const void *a, size_t na, const void *b, size_t nb, const void *c, size_t nc,
                const void *d, size_t nd, const void *e, size_t ne)
{
    unsigned n = (unsigned)(na + nb + nc + nd + ne);
    fwrite(tag, 1, 4, g_dump);
    fwrite(&n, 4, 1, g_dump);
    if (na) fwrite(a, 1, na, g_dump);
    if (nb) fwrite(b, 1, nb, g_dump);
    if (nc) fwrite(c, 1, nc, g_dump);
    if (nd) fwrite(d, 1, nd, g_dump);
    if (ne) fwrite(e, 1, ne, g_dump);
}

/* redirect "call rel32" at VA to fn; returns original target */
static void *redirect(ULONG_PTR va, void *fn)
{
    BYTE *site = g_eng + RVA(va), *stub = g_tramp + 16 * g_ntramp++;
    DWORD old;
    int rel;
    void *orig;
    if (site[0] != 0xE8) { printf("site %llx is not a call\n", (unsigned long long)va); exit(1); }
    orig = site + 5 + *(int *)(site + 1);
    stub[0] = 0x48; stub[1] = 0xB8; *(void **)(stub + 2) = fn; stub[10] = 0xFF; stub[11] = 0xE0; /* mov rax,fn; jmp rax */
    rel = (int)(stub - (site + 5));
    VirtualProtect(site, 5, PAGE_EXECUTE_READWRITE, &old);
    *(int *)(site + 1) = rel;
    VirtualProtect(site, 5, old, &old);
    return orig;
}

/* ---- CSpsVocoder prepare (FUN_18010ca5c float / FUN_18010c148 int) ---- */
typedef unsigned long long (*Prep_t)(BYTE *, BYTE *, unsigned long long, int);
static Prep_t o_prepf, o_prepi;
static void dumpvoc(BYTE *v, const char *which)
{
    BYTE *exc = *(BYTE **)(v + 0x48), *syn = *(BYTE **)(v + 0x50), *d = *(BYTE **)(v + 0xb0);
    static int once;
    if (!once++) {
        printf("[voc %s] fs=%u shift=%u intmode=%d silNoise=%d nusMix(+7c)=%d +e4=%d NNstream(+a8)=%d power(+f0)=%d itfte(+10c)=%d\n",
               which, *(unsigned *)(v + 8), *(unsigned *)(v + 0xc), *(int *)(v + 0x38), *(int *)(v + 0x3c), *(int *)(v + 0x7c),
               *(int *)(v + 0xe4), *(int *)(v + 0xa8), *(int *)(v + 0xf0), *(int *)(v + 0x10c));
        printf("  exc vtbl rva=%llx syn vtbl rva=%llx smoother(+30)=%p sharpen(+40)=%p spectrumwarp(+f4)=%g\n",
               (unsigned long long)(*(BYTE **)exc - g_eng), (unsigned long long)(*(BYTE **)syn - g_eng), *(void **)(v + 0x30),
               *(void **)(v + 0x40), *(float *)(v + 0xf4));
        printf("  exc gains 1058=%.9g 105c=%.9g synth+10(isLPC)=%d\n", *(float *)(exc + 0x1058), *(float *)(exc + 0x105c),
               *(int *)(syn + 0x10));
        {
            BYTE *s = *(BYTE **)(v + 0x40);
            if (s) printf("  sharpen: freqdep=%d multi=%d intervals=%d iters=%d step=%g top=%g low=%g high=%g\n", *(int *)(s + 8),
                          *(int *)(s + 0xc), *(int *)(s + 0x10), *(int *)(s + 0x14), *(float *)(s + 0x18), *(float *)(s + 0x1c),
                          *(float *)(s + 0x20), *(float *)(s + 0x24));
        }
    }
    if (d) {
        static const char *nm[8] = {"F0", "LSF", "gain", "MBE", "power", "s50", "s58", "s60"};
        int i;
        Mat *dur = *(Mat **)(d + 0x18);
        printf("[chunk] phones0=%d nframes=%u headTrim=%u tailTrim=%u dur=%ux%u", *(int *)d, *(unsigned *)(d + 4),
               *(unsigned *)(d + 8), *(unsigned *)(d + 12), dur ? dur->rows : 0, dur ? dur->cols : 0);
        for (i = 0; i < 8; i++) {
            Mat *m = *(Mat **)(d + 0x28 + 8 * i);
            if (m && m->data) printf(" %s=%ux%u", nm[i], m->rows, m->cols);
        }
        printf("\n");
    }
}
static unsigned long long h_prepf(BYTE *v, BYTE *utt, unsigned long long a, int b)
{
    unsigned long long r = o_prepf(v, utt, a, b);
    dumpvoc(v, "float");
    return r;
}
static unsigned long long h_prepi(BYTE *v, BYTE *utt, unsigned long long a, int b)
{
    unsigned long long r = o_prepi(v, utt, a, b);
    dumpvoc(v, "int");
    return r;
}

/* ---- LsfSharpen (FUN_180012408(Mat *lsf, sharpenSettings *, flagsview *)) ---- */
typedef int (*Shrp_t)(Mat *, void *, void *);
static Shrp_t o_shrp;
static int h_shrp(Mat *m, void *s, void *f)
{
    size_t n = (size_t)m->rows * m->cols;
    float *before = (float *)malloc(n * 4);
    unsigned hdr[2] = {m->rows, m->cols};
    int r;
    memcpy(before, m->data, n * 4);
    r = o_shrp(m, s, f);
    rec("SHRP", hdr, 8, before, n * 4, m->data, n * 4, 0, 0, 0, 0);
    free(before);
    return r;
}

/* ---- end-of-utterance vocoder reset FUN_18011024c(vocoder) ---- */
typedef void (*Rst_t)(void *);
static Rst_t o_rst;
static void h_rst(void *v) { o_rst(v); rec("RSET", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }

/* ---- excitation ---- */
typedef unsigned long long (*Exc0_t)(void *, Mat *, float *, unsigned, unsigned);
typedef unsigned long long (*Exc1_t)(void *, Mat *, Mat *, float *, unsigned, unsigned);
static Exc0_t o_exc0;
static Exc1_t o_exc1;
static unsigned long long h_exc0(void *e, Mat *f0, float *out, unsigned n, unsigned sh)
{
    unsigned long long r = o_exc0(e, f0, out, n, sh);
    unsigned hdr[4] = {f0->rows, f0->cols, n, sh};
    rec("EXC0", hdr, 16, f0->data, (size_t)f0->rows * f0->cols * 4, out, (size_t)n * 4, 0, 0, 0, 0);
    return r;
}
static unsigned long long h_exc1(void *e, Mat *f0, Mat *mbe, float *out, unsigned n, unsigned sh)
{
    unsigned long long r = o_exc1(e, f0, mbe, out, n, sh);
    unsigned hdr[6] = {f0->rows, f0->cols, mbe->rows, mbe->cols, n, sh};
    rec("EXC1", hdr, 24, f0->data, (size_t)f0->rows * f0->cols * 4, mbe->data, (size_t)mbe->rows * mbe->cols * 4, out,
        (size_t)n * 4, 0, 0);
    return r;
}

/* ---- int (fixed-point) path: Zira/Mark (APM header flag at file 0x24 = 1) ---- */
typedef struct { unsigned rows, cols; int *data; } IMat;
typedef unsigned long long (*IExc0_t)(void *, IMat *, int *, unsigned, unsigned);
static IExc0_t o_iexc0;
static unsigned long long h_iexc0(void *e, IMat *f0, int *out, unsigned n, unsigned sh)
{
    unsigned long long r = o_iexc0(e, f0, out, n, sh);
    unsigned hdr[4] = {f0->rows, f0->cols, n, sh};
    rec("IEX0", hdr, 16, f0->data, (size_t)f0->rows * f0->cols * 4, out, (size_t)n * 4, 0, 0, 0, 0);
    return r;
}
typedef int (*IShrp_t)(IMat *, void *, void *);
static IShrp_t o_ishrp;
static int h_ishrp(IMat *m, void *s, void *f)
{
    size_t n = (size_t)m->rows * m->cols;
    int *before = (int *)malloc(n * 4);
    unsigned hdr[2] = {m->rows, m->cols};
    int r;
    memcpy(before, m->data, n * 4);
    r = o_ishrp(m, s, f);
    rec("ISHP", hdr, 8, before, n * 4, m->data, n * 4, 0, 0, 0, 0);
    free(before);
    return r;
}
typedef unsigned long long (*ISyn_t)(void *, IMat *, IMat *, int *, short *, unsigned, unsigned, int, float, float *, IMat *,
                                     IMat *, unsigned);
static ISyn_t o_isyn;
static unsigned long long h_isyn(void *s, IMat *lsf, IMat *g, int *exc, short *out, unsigned n, unsigned sh, int itfte, float warp,
                                 float *warpv, IMat *pw, IMat *f0, unsigned fs)
{
    int *ecopy = (int *)malloc((size_t)n * 4);
    unsigned long long r;
    struct { unsigned rows, order, grows, gcols, n, sh; int itfte; float warp; unsigned hw, hp; } h;
    memcpy(ecopy, exc, (size_t)n * 4);
    r = o_isyn(s, lsf, g, exc, out, n, sh, itfte, warp, warpv, pw, f0, fs);
    h.rows = lsf->rows; h.order = lsf->cols; h.grows = g->rows; h.gcols = g->cols; h.n = n; h.sh = sh; h.itfte = itfte;
    h.warp = warp; h.hw = warpv != NULL; h.hp = pw != NULL;
    rec("ISYN", &h, sizeof h, lsf->data, (size_t)lsf->rows * lsf->cols * 4, g->data, (size_t)g->rows * g->cols * 4, ecopy,
        (size_t)n * 4, out, (size_t)n * 2);
    free(ecopy);
    return r;
}

/* ---- synthesis FUN_18006b620 ---- */
typedef unsigned long long (*Syn_t)(void *, Mat *, Mat *, float *, short *, unsigned, unsigned, int, float, float *, Mat *,
                                    Mat *, unsigned);
static Syn_t o_syn;
static unsigned long long h_syn(void *s, Mat *lsf, Mat *g, float *exc, short *out, unsigned n, unsigned sh, int itfte, float warp,
                                float *warpv, Mat *pw, Mat *f0, unsigned fs)
{
    float *ecopy = (float *)malloc((size_t)n * 4);
    unsigned long long r;
    struct { unsigned rows, order, grows, gcols, n, sh; int itfte; float warp; unsigned hw, hp; } h;
    memcpy(ecopy, exc, (size_t)n * 4);
    r = o_syn(s, lsf, g, exc, out, n, sh, itfte, warp, warpv, pw, f0, fs);
    h.rows = lsf->rows; h.order = lsf->cols; h.grows = g->rows; h.gcols = g->cols; h.n = n; h.sh = sh; h.itfte = itfte;
    h.warp = warp; h.hw = warpv != NULL; h.hp = pw != NULL;
    rec("SYN0", &h, sizeof h, lsf->data, (size_t)lsf->rows * lsf->cols * 4, g->data, (size_t)g->rows * g->cols * 4, ecopy,
        (size_t)n * 4, out, (size_t)n * 2);
    free(ecopy);
    return r;
}

int wmain(int argc, wchar_t **argv)
{
    ISpVoice *voice = NULL;
    ISpObjectToken *tok = NULL;
    ISpStream *stream = NULL;
    WAVEFORMATEX wf = {WAVE_FORMAT_PCM, 1, 16000, 32000, 2, 16, 0};
    HRESULT hr;
    ULONG_PTR a;
    if (argc < 3) { fwprintf(stderr, L"usage: vocprobe \"text\" out.wav [token]\n"); return 1; }
    setvbuf(stdout, NULL, _IONBF, 0);
    g_eng = (BYTE *)LoadLibraryW(ENGINE);
    if (!g_eng) { fprintf(stderr, "cannot load engine\n"); return 1; }
    for (a = (ULONG_PTR)g_eng - 0x10000; a > (ULONG_PTR)g_eng - 0x70000000 && !g_tramp; a -= 0x10000)
        g_tramp = (BYTE *)VirtualAlloc((void *)a, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!g_tramp) { fprintf(stderr, "no trampoline page\n"); return 1; }
    g_dump = fopen("vocdump.bin", "wb");
    o_prepf = (Prep_t)redirect(0x1800327a6, (void *)h_prepf);
    o_prepi = (Prep_t)redirect(0x18003279c, (void *)h_prepi);
    o_shrp = (Shrp_t)redirect(0x18010d2b0, (void *)h_shrp);
    o_exc0 = (Exc0_t)redirect(0x18000a060, (void *)h_exc0);
    o_exc1 = (Exc1_t)redirect(0x18000a07e, (void *)h_exc1);
    o_syn = (Syn_t)redirect(0x18000a42f, (void *)h_syn);
    o_rst = (Rst_t)redirect(0x1800321e1, (void *)h_rst);
    o_iexc0 = (IExc0_t)redirect(0x180074ce6, (void *)h_iexc0);
    o_ishrp = (IShrp_t)redirect(0x18010c99c, (void *)h_ishrp);
    o_isyn = (ISyn_t)redirect(0x180074f15, (void *)h_isyn);
    CoInitialize(NULL);
    hr = CoCreateInstance(&CLSID_SpVoice, NULL, CLSCTX_ALL, &IID_ISpVoice, (void **)&voice);
    if (SUCCEEDED(hr)) hr = CoCreateInstance(&CLSID_SpObjectToken, NULL, CLSCTX_ALL, &IID_ISpObjectToken, (void **)&tok);
    if (SUCCEEDED(hr)) hr = ISpObjectToken_SetId(tok, NULL, argc > 3 ? argv[3] : DAVID, FALSE);
    if (SUCCEEDED(hr)) hr = ISpVoice_SetVoice(voice, tok);
    if (FAILED(hr)) { fprintf(stderr, "voice %08lx\n", hr); return 1; }
    hr = CoCreateInstance(&CLSID_SpStream, NULL, CLSCTX_ALL, &IID_ISpStream, (void **)&stream);
    if (SUCCEEDED(hr)) hr = ISpStream_BindToFile(stream, argv[2], SPFM_CREATE_ALWAYS, &SPDFID_WaveFormatEx, &wf, 0);
    if (SUCCEEDED(hr)) hr = ISpVoice_SetOutput(voice, (IUnknown *)stream, TRUE);
    if (FAILED(hr)) { fprintf(stderr, "output %08lx\n", hr); return 1; }
    hr = ISpVoice_Speak(voice, argv[1], wcschr(argv[1], L'<') ? SPF_IS_XML : SPF_DEFAULT, NULL);
    printf("Speak hr=%08lx\n", hr);
    ISpStream_Close(stream);
    ISpStream_Release(stream);
    ISpObjectToken_Release(tok);
    ISpVoice_Release(voice);
    CoUninitialize();
    fclose(g_dump);
    return 0;
}
