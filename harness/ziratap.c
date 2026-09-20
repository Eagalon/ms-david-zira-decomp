/* ziratap: drive the real OneCore en-US engine (MSTTSEngine_OneCore.dll, x64) through SAPI5 and log
 * what it does.  Mapping aid only (see notes/frontend.md "SAPI integration / hooking plan").
 *
 * 64-bit.  Build (x64 MSVC env):  build_ziratap.bat
 * Usage:  ziratap.exe <voice> "text"|@file.txt out.wav [rate]
 *   voice = david | zira | mark   (OneCore tokens under HKLM\SOFTWARE\Microsoft\Speech_OneCore\Voices\Tokens)
 *
 * Hooks (RVAs for MSTTSEngine_OneCore.dll 10.3.21207.0, MD5 D7D84E2B439E4EDC0F691EFD2085F4FC):
 *   0x029190  trace logger  void Log(int level, const wchar_t *fmt, ...)  -> replaced (jmp) by my_log,
 *             which prints every trace line ("[TTS]Entering: CTextProcessor::Process", "[TTS] InputText = ..",
 *             "<Fragments>" dumps, init messages).  The original only formats + EventWrite()s to ETW
 *             provider {9502132b-fbe0-4f27-9165-6dc8232a2b67}; nothing else depends on it.
 *   0x175210  ISpTTSEngine vtable of CComObject<CTTSEngineCom>; slot 3 = Speak (0x08b210) -> my_speak,
 *             which installs a stage observer at CTTSEngine+0x578 before chaining to the original.
 *             CTTSEngine::Speak (0x028288) calls  obs->vt[0](obs, handlerId, phase(0=before,1=after), utt)
 *             around every handler's Process (return 1 in phase 0 = skip that handler).
 */
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#include <windows.h>
#include <sapi.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define ENGINE_DLL L"C:\\Windows\\System32\\Speech_OneCore\\Engines\\TTS\\MSTTSEngine_OneCore.dll"
#define TOKROOT L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices\\Tokens\\"

#define RVA_LOG        0x029190
#define RVA_SPEAK      0x08b210
#define RVA_VT_TTSENG  0x175210   /* ISpTTSEngine vtable (QI,AddRef,Release,Speak,GetOutputFormat) */
#define OFF_ENGINE_FROM_ITTS 0x68 /* this(ISpTTSEngine = obj+8) + 0x68 = obj+0x70 -> CTTSEngine* */
#define OFF_STAGE_OBS  0x578      /* CTTSEngine+0x578 : stage observer */

static BYTE *g_base;
static FILE *g_out;
static CRITICAL_SECTION g_lock;

/* ---- trace logger replacement ---- */
static void my_log(int level, const wchar_t *fmt, ...)
{
    wchar_t buf[8192];
    va_list ap;
    va_start(ap, fmt);
    /* the engine uses MS legacy wide semantics: %s = wide, %S = narrow (same as _vsnwprintf) */
    _vsnwprintf(buf, 8191, fmt, ap);
    va_end(ap);
    buf[8191] = 0;
    EnterCriticalSection(&g_lock);
    fwprintf(g_out, L"LOG%d %ls\n", level, buf);
    fflush(g_out);
    LeaveCriticalSection(&g_lock);
}

static void write_jmp(BYTE *at, void *to)
{
    DWORD old;
    VirtualProtect(at, 14, PAGE_EXECUTE_READWRITE, &old);
    at[0] = 0xFF; at[1] = 0x25; *(DWORD *)(at + 2) = 0;   /* jmp [rip+0] */
    *(void **)(at + 6) = to;
    VirtualProtect(at, 14, old, &old);
    FlushInstructionCache(GetCurrentProcess(), at, 14);
}

/* ---- stage observer placed at CTTSEngine+0x578 ---- */
typedef struct Obs { void **vt; } Obs;
static int __cdecl obs_cb(Obs *self, unsigned id, int phase, void *utt)
{
    (void)self;
    EnterCriticalSection(&g_lock);
    fwprintf(g_out, L"STAGE id=%u %ls utt=%p\n", id, phase ? L"after" : L"before", utt);
    fflush(g_out);
    LeaveCriticalSection(&g_lock);
    /* per-stage dumps of the utterance structure go here (layouts: notes/frontend.md) */
    return 0;
}
static void *g_obs_vt[1] = { (void *)obs_cb };
static Obs g_obs = { g_obs_vt };

/* sapiddk.h does not compile as C; replicate the one struct we need (layout = sapiddk.h) */
typedef struct SPVTEXTFRAG { struct SPVTEXTFRAG *pNext; SPVSTATE State; LPCWSTR pTextStart;
                             ULONG ulTextLen; ULONG ulTextSrcOffset; } SPVTEXTFRAG;
typedef void ISpTTSEngineSite;

typedef HRESULT (STDMETHODCALLTYPE *SpeakFn)(void *, DWORD, REFGUID, const WAVEFORMATEX *,
                                             const SPVTEXTFRAG *, ISpTTSEngineSite *);
static SpeakFn g_orig_speak;

static void dump_frags(const SPVTEXTFRAG *f)
{
    for (; f; f = f->pNext) {
        fwprintf(g_out, L"FRAG act=%d lang=%04x emph=%d rate=%d vol=%u pitch=%d/%d sil=%u pos=%u cat=%ls off=%u len=%u \"%.*ls\"\n",
                 f->State.eAction, f->State.LangID, f->State.EmphAdj, f->State.RateAdj, f->State.Volume,
                 f->State.PitchAdj.MiddleAdj, f->State.PitchAdj.RangeAdj, f->State.SilenceMSecs,
                 f->State.ePartOfSpeech, f->State.Context.pCategory ? f->State.Context.pCategory : L"-",
                 f->ulTextSrcOffset, f->ulTextLen, (int)f->ulTextLen, f->pTextStart ? f->pTextStart : L"");
    }
}

static HRESULT STDMETHODCALLTYPE my_speak(void *self, DWORD flags, REFGUID fmt, const WAVEFORMATEX *wfx,
                                          const SPVTEXTFRAG *frags, ISpTTSEngineSite *site)
{
    BYTE *eng = *(BYTE **)((BYTE *)self + OFF_ENGINE_FROM_ITTS);
    EnterCriticalSection(&g_lock);
    fwprintf(g_out, L"SPEAK flags=%lu engine=%p\n", flags, eng);
    dump_frags(frags);
    LeaveCriticalSection(&g_lock);
    if (eng) *(Obs **)(eng + OFF_STAGE_OBS) = &g_obs;
    return g_orig_speak(self, flags, fmt, wfx, frags, site);
}

static void install_hooks(void)
{
    DWORD old;
    void **slot = (void **)(g_base + RVA_VT_TTSENG + 3 * sizeof(void *));
    if (*slot != g_base + RVA_SPEAK) {
        fwprintf(stderr, L"unexpected Speak slot %p (engine build mismatch?)\n", *slot);
        ExitProcess(2);
    }
    g_orig_speak = (SpeakFn)*slot;
    VirtualProtect(slot, sizeof(void *), PAGE_READWRITE, &old);
    *slot = (void *)my_speak;
    VirtualProtect(slot, sizeof(void *), old, &old);
    /* prologue check: mov rax,rsp ; mov [rax+10h],rdx ; mov [rax+18h],r8 ; mov [rax+20h],r9 (15 bytes) */
    if (memcmp(g_base + RVA_LOG, "\x48\x8b\xc4\x48\x89\x50\x10", 7) != 0) {
        fwprintf(stderr, L"unexpected logger prologue\n");
        ExitProcess(2);
    }
    write_jmp(g_base + RVA_LOG, (void *)my_log);
}

static wchar_t *read_text(const wchar_t *arg)
{
    if (arg[0] != L'@') return _wcsdup(arg);
    FILE *f = _wfopen(arg + 1, L"rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET);
    char *b = malloc(n + 1); fread(b, 1, n, f); b[n] = 0; fclose(f);
    int off = (n >= 3 && (BYTE)b[0] == 0xEF && (BYTE)b[1] == 0xBB && (BYTE)b[2] == 0xBF) ? 3 : 0;
    int wn = MultiByteToWideChar(CP_UTF8, 0, b + off, -1, NULL, 0);
    wchar_t *w = malloc(wn * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, b + off, -1, w, wn);
    free(b);
    return w;
}

static void write_wav(const wchar_t *path, const BYTE *pcm, DWORD n, DWORD rate)
{
    FILE *f = _wfopen(path, L"wb");
    DWORD v; WORD w;
    fwrite("RIFF", 1, 4, f); v = 36 + n; fwrite(&v, 4, 1, f); fwrite("WAVEfmt ", 1, 8, f);
    v = 16; fwrite(&v, 4, 1, f); w = 1; fwrite(&w, 2, 1, f); fwrite(&w, 2, 1, f);
    fwrite(&rate, 4, 1, f); v = rate * 2; fwrite(&v, 4, 1, f); w = 2; fwrite(&w, 2, 1, f);
    w = 16; fwrite(&w, 2, 1, f); fwrite("data", 1, 4, f); fwrite(&n, 4, 1, f);
    fwrite(pcm, 1, n, f); fclose(f);
}

int wmain(int argc, wchar_t **argv)
{
    if (argc < 4) {
        fwprintf(stderr, L"usage: ziratap david|zira|mark \"text\"|@file out.wav [rate]\n");
        return 1;
    }
    const wchar_t *voice = argv[1];
    wchar_t *text = read_text(argv[2]);
    DWORD rate = argc > 4 ? _wtoi(argv[4]) : 16000;
    wchar_t tokid[512];
    const wchar_t *tn = !_wcsicmp(voice, L"zira") ? L"MSTTS_V110_enUS_ZiraM"
                      : !_wcsicmp(voice, L"mark") ? L"MSTTS_V110_enUS_MarkM" : L"MSTTS_V110_enUS_DavidM";
    swprintf(tokid, 512, L"%ls%ls", TOKROOT, tn);
    InitializeCriticalSection(&g_lock);
    g_out = stdout;

    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    g_base = (BYTE *)LoadLibraryW(ENGINE_DLL);   /* same module SAPI's CoCreateInstance will get */
    if (!g_base) { fwprintf(stderr, L"cannot load engine\n"); return 1; }
    install_hooks();

    ISpObjectToken *tok = NULL;
    ISpVoice *v = NULL;
    ISpStream *st = NULL;
    IStream *mem = NULL;
    HRESULT hr = CoCreateInstance(&CLSID_SpObjectToken, NULL, CLSCTX_ALL, &IID_ISpObjectToken, (void **)&tok);
    if (SUCCEEDED(hr)) hr = ISpObjectToken_SetId(tok, NULL, tokid, FALSE);
    if (SUCCEEDED(hr)) hr = CoCreateInstance(&CLSID_SpVoice, NULL, CLSCTX_ALL, &IID_ISpVoice, (void **)&v);
    if (SUCCEEDED(hr)) hr = ISpVoice_SetVoice(v, tok);
    if (FAILED(hr)) { fwprintf(stderr, L"voice setup failed %08lx\n", hr); return 1; }

    WAVEFORMATEX wf = { WAVE_FORMAT_PCM, 1, rate, rate * 2, 2, 16, 0 };
    CreateStreamOnHGlobal(NULL, TRUE, &mem);
    CoCreateInstance(&CLSID_SpStream, NULL, CLSCTX_ALL, &IID_ISpStream, (void **)&st);
    hr = ISpStream_SetBaseStream(st, mem, &SPDFID_WaveFormatEx, &wf);
    if (SUCCEEDED(hr)) hr = ISpVoice_SetOutput(v, (IUnknown *)st, TRUE);
    ULONGLONG interest = SPFEI(SPEI_WORD_BOUNDARY) | SPFEI(SPEI_SENTENCE_BOUNDARY) | SPFEI(SPEI_PHONEME) |
                         SPFEI(SPEI_VISEME) | SPFEI(SPEI_TTS_BOOKMARK);
    ISpVoice_SetInterest(v, interest, interest);
    if (SUCCEEDED(hr)) hr = ISpVoice_Speak(v, text, SPF_DEFAULT, NULL);
    fwprintf(g_out, L"SPEAK hr=%08lx\n", hr);

    SPEVENT ev; ULONG got;
    while (ISpVoice_GetEvents(v, 1, &ev, &got) == S_OK && got == 1) {
        fwprintf(g_out, L"EVENT id=%u off=%llu wParam=%llu lParam=%lld\n", ev.eEventId,
                 ev.ullAudioStreamOffset, (ULONGLONG)ev.wParam, (LONGLONG)ev.lParam);
        if (ev.elParamType == SPET_LPARAM_IS_STRING || ev.elParamType == SPET_LPARAM_IS_POINTER)
            CoTaskMemFree((void *)ev.lParam);
    }

    HGLOBAL hg; STATSTG ss;
    GetHGlobalFromStream(mem, &hg);
    IStream_Stat(mem, &ss, STATFLAG_NONAME);
    BYTE *p = GlobalLock(hg);
    write_wav(argv[3], p, (DWORD)ss.cbSize.QuadPart, rate);
    GlobalUnlock(hg);
    return FAILED(hr);
}
