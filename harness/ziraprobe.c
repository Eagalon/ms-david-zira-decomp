/* ziraprobe: x64 probe of the OneCore TTS engine (MSTTSEngine_OneCore.dll) pipeline.
 * Speaks text through SAPI5 with the "Microsoft David Desktop" token (which is registered with the OneCore
 * engine CLSID {179F3D56-...} and VoicePath ...\Speech_OneCore\...\M1033David), patches handler vtables
 * (ITTSHandler slot 3 = Process) and the CTTSFeatureExtractionEngine slot 3 (per-feature value arrays),
 * and prints what runs. Build (x64 VS env): cl /nologo /O2 /W3 ziraprobe.c ole32.lib sapi.lib
 * Usage: ziraprobe.exe "text" out.wav [token-id]  */
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#include <windows.h>
#include <sapi.h>
#include <stdio.h>
#include <stdlib.h>

#define ENGINE L"C:/Windows/System32/speech_onecore/engines/tts/MSTTSEngine_OneCore.dll"
#define DAVID L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech\\Voices\\Tokens\\TTS_MS_EN-US_DAVID_11.0"

static BYTE *g_eng;
typedef long (*Proc_t)(void *, void *, void *, void *);
#define NH 9
static const struct { const char *name; unsigned vt; } H[NH] = {
    {"CTextProcessor", 0x175d00}, {"CLinguisticProsodyTagger", 0x171328}, {"CTTSUnitGenerator", 0x1757a8},
    {"CAcousticProsodyTagger", 0x16ea58}, {"CAcousticProsodyTaggerAnchor", 0x175938},
    {"CLongUnitLatticeGenerator", 0x177118}, {"CUnitLatticeGenerator", 0x177198}, {"CUnitSelector", 0x177720},
    {"CWaveGenerator", 0x172ff0}};
static Proc_t o_proc[NH];
static long call(int i, void *a, void *b, void *c, void *d)
{
    long hr;
    printf("-> %s::Process(this=%p utt=%p)\n", H[i].name, a, b);
    if (i == 3) { /* CAcousticProsodyTagger: predictor vector at this+0xa8 (data) / +0xb0 (count), elements CAcousticPredictorBase* */
        BYTE **v = *(BYTE ***)((BYTE *)a + 0xa8);
        size_t n = *(size_t *)((BYTE *)a + 0xb0), k;
        printf("   predictors(%zu):", n);
        for (k = 0; k < n; k++) printf(" vt=+%llx", (unsigned long long)(*(BYTE **)v[k] - g_eng));
        printf("  utt+0x2c0=%d\n", *(int *)((BYTE *)b + 0x2c0));
    }
    hr = o_proc[i](a, b, c, d);
    printf("<- %s hr=%08lx\n", H[i].name, hr);
    return hr;
}
#define HP(i) static long h##i(void *a, void *b, void *c, void *d) { return call(i, a, b, c, d); }
HP(0) HP(1) HP(2) HP(3) HP(4) HP(5) HP(6) HP(7) HP(8)
static void *hp[NH] = {h0, h1, h2, h3, h4, h5, h6, h7, h8};

/* CTTSFeatureExtractionEngine vtable slot 3 (0x18005bfc0):
 * (this, CTTSUtterance *utt, FeatureMeta metas[n] (0x100 B each), FeatureValues out[n] (0x20 B each), int n)
 * out[i] = {Value *data; size_t count; size_t cap; int grow}; Value = 16 B {i32 kind; i32 ?; union{i32; wchar_t*}} */
typedef long (*Fx_t)(void *, void *, BYTE *, BYTE *, int);
static Fx_t o_fx;
static long h_fx(void *self, void *utt, BYTE *metas, BYTE *out, int n)
{
    long hr = o_fx(self, utt, metas, out, n);
    int i;
    size_t j;
    printf("FeatureExtract n=%d hr=%08lx\n", n, hr);
    for (i = 0; i < n; i++) {
        BYTE *rec = out + 0x20 * i, *data = *(BYTE **)rec;
        size_t cnt = *(size_t *)(rec + 8);
        printf("  f%02d cnt=%zu:", i, cnt);
        for (j = 0; j < cnt && j < 40; j++) {
            int kind = *(int *)(data + 16 * j);
            if (kind == 2) printf(" '%ls'", *(wchar_t **)(data + 16 * j + 8));
            else if (kind == -1) printf(" null");
            else printf(" %d:%d", kind, *(int *)(data + 16 * j + 8));
        }
        printf("\n");
    }
    return hr;
}

/* streaming interface (ITTSStreamHandler at object+8, 10 slots): 6 Begin(utt) 7 Step() 8 HasMore(int*) 9 End() */
#define NS 4
static const struct { const char *name; unsigned vt; } S[NS] = {
    {"CWaveGenerator", 0x173060}, {"CUnitLatticeGenerator", 0x1771f8}, {"CUnitSelector", 0x1776c8},
    {"CAcousticProsodyTagger(stream)", 0x16eae8}};
typedef long (*S1_t)(void *, void *, void *, void *);
static S1_t o_s[NS][4];
static int g_steps[NS];
static long scall(int i, int k, void *a, void *b, void *c, void *d)
{
    long hr = o_s[i][k](a, b, c, d);
    if (k == 1) g_steps[i]++;
    else if (k != 2) printf("   [stream] %s slot%d(%p,%p) hr=%08lx steps=%d\n", S[i].name, 6 + k, a, b, hr, g_steps[i]);
    if (k == 3) g_steps[i] = 0;
    return hr;
}
#define SP(i, k) static long s##i##k(void *a, void *b, void *c, void *d) { return scall(i, k, a, b, c, d); }
SP(0,0) SP(0,1) SP(0,2) SP(0,3) SP(1,0) SP(1,1) SP(1,2) SP(1,3) SP(2,0) SP(2,1) SP(2,2) SP(2,3)
static void *sp[3][4] = {{s00, s01, s02, s03}, {s10, s11, s12, s13}, {s20, s21, s22, s23}};

/* CStreamHandlersAdapter (vtbl RVA 0x178ac0) slot 3 = Process(this, utt): list at this+0x10 of {next, prev, ITtsStreamHandler*} */
static Proc_t o_adp;
static long h_adp(void *a, void *b, void *c, void *d)
{
    BYTE **n = *(BYTE ***)((BYTE *)a + 0x10);
    long hr;
    printf("-> CStreamHandlersAdapter::Process(utt=%p) handlers:", b);
    for (; n; n = (BYTE **)n[0]) {
        BYTE *obj = (BYTE *)n[2];
        printf(" [%p vt=+%llx]", obj, (unsigned long long)(*(BYTE **)obj - g_eng));
    }
    printf("\n");
    { /* utt+0xe8: segment list {node *head; node *tail; size_t count}; node {next, prev, CTTSSegment*}; seg+0xc0 = domain wchar_t* (from CWaveGenerator Begin) */
        BYTE *u = (BYTE *)b, **sn = *(BYTE ***)(u + 0xe8);
        printf("   utt+0x78='%ls' segments=%zu:", *(wchar_t **)(u + 0x78) ? *(wchar_t **)(u + 0x78) : L"(null)", *(size_t *)(u + 0xf8));
        for (; sn; sn = (BYTE **)sn[0]) { wchar_t *d = *(wchar_t **)((BYTE *)sn[2] + 0xc0); printf(" '%ls'", d ? d : L"(null)"); }
        printf("\n");
    }
    hr = o_adp(a, b, c, d);
    printf("<- CStreamHandlersAdapter hr=%08lx\n", hr);
    {
        BYTE *u = (BYTE *)b, **sn = *(BYTE ***)(u + 0xe8);
        printf("   after: utt+0x78='%ls' segments=%zu:", *(wchar_t **)(u + 0x78) ? *(wchar_t **)(u + 0x78) : L"(null)", *(size_t *)(u + 0xf8));
        for (; sn; sn = (BYTE **)sn[0]) { wchar_t *d = *(wchar_t **)((BYTE *)sn[2] + 0xc0); printf(" '%ls'", d ? d : L"(null)"); }
        printf("\n");
    }
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

int wmain(int argc, wchar_t **argv)
{
    ISpVoice *voice = NULL;
    ISpObjectToken *tok = NULL;
    ISpStream *stream = NULL;
    WAVEFORMATEX wf = {WAVE_FORMAT_PCM, 1, 16000, 32000, 2, 16, 0};
    HRESULT hr;
    int i;
    if (argc < 3) { fwprintf(stderr, L"usage: ziraprobe \"text\" out.wav [token]\n"); return 1; }
    setvbuf(stdout, NULL, _IONBF, 0);
    g_eng = (BYTE *)LoadLibraryW(ENGINE);
    if (!g_eng) { fprintf(stderr, "cannot load engine\n"); return 1; }
    printf("engine base %p\n", g_eng);
    for (i = 0; i < NH; i++) patch((void **)(g_eng + H[i].vt) + 3, hp[i], (void **)&o_proc[i]);
    patch((void **)(g_eng + 0x1714b8) + 3, (void *)h_fx, (void **)&o_fx);
    for (i = 0; i < 3; i++) { int k; for (k = 0; k < 4; k++) patch((void **)(g_eng + S[i].vt) + 6 + k, sp[i][k], (void **)&o_s[i][k]); }
    patch((void **)(g_eng + 0x178ac0) + 3, (void *)h_adp, (void **)&o_adp);
    if (getenv("NOFX")) patch((void **)(g_eng + 0x1714b8) + 3, (void *)o_fx, (void **)&o_fx);
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
    return 0;
}
