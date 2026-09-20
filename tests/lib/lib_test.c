/* Tests for the David / Zira / Mark host library (src/zira_tts.h).  Sub-commands:
 *
 *   lib_test wav    VOICE OUT.wav [--data D] [--rate N] [--volume N] [--pitch N] [--emotion E] [--xml] TEXT|@FILE
 *       speak through the library and write a WAV (byte-comparable with zira_say.exe's output)
 *   lib_test events VOICE [--data D] [--xml] TEXT|@FILE
 *       print one "type|audio_sample|text_pos|text_len|text" line per sentence/word/bookmark/end event
 *   lib_test cancel VOICE [--data D]
 *       call zira_tts_cancel from another thread in the middle of a long text and report how much audio still
 *       arrived afterwards (must be at most a chunk or two)
 *   lib_test emotions VOICE [--data D]
 *       list the voice's [EmotionRecipe] names
 */
#include "zira_tts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
typedef HANDLE thread_t;
typedef DWORD(WINAPI *threadfn_t)(void *);
#define THREAD_RET DWORD WINAPI
static void nap(int ms) { Sleep(ms); }
static void thread_start(thread_t *h, threadfn_t fn, void *arg) { *h = CreateThread(NULL, 0, fn, arg, 0, NULL); }
static void thread_join(thread_t h) { WaitForSingleObject(h, INFINITE); CloseHandle(h); }
#else
#include <pthread.h>
#include <unistd.h>
typedef pthread_t thread_t;
typedef void *(*threadfn_t)(void *);
#define THREAD_RET void *
static void nap(int ms) { usleep((unsigned)ms * 1000); }
static void thread_start(thread_t *h, threadfn_t fn, void *arg) { pthread_create(h, NULL, fn, arg); }
static void thread_join(thread_t h) { pthread_join(h, NULL); }
#endif

typedef struct {
    FILE *f;
    const char *text;
    int print_events;
    long stop_after;        /* 0 = never: else the audio callback returns nonzero past this many samples */
    volatile long got;      /* samples handed to us */
} ctx;

static void put(FILE *f, unsigned v, int n)
{
    int i;
    for (i = 0; i < n; i++) fputc((int)((v >> (8 * i)) & 0xFF), f);
}

static int on_audio(const int16_t *pcm, size_t n, void *user)
{
    ctx *c = (ctx *)user;
    size_t i;
    if (c->f)
        for (i = 0; i < n; i++) put(c->f, (unsigned)(uint16_t)pcm[i], 2);
    c->got += (long)n;
    return c->stop_after && c->got >= c->stop_after;
}

static void on_event(const zira_event *e, void *user)
{
    ctx *c = (ctx *)user;
    static const char *const names[] = {"?", "sentence", "word", "bookmark", "end"};
    if (!c->print_events) return;
    printf("%s|%llu|%ld|%ld|", names[e->type > 0 && e->type <= 4 ? e->type : 0], (unsigned long long)e->audio_pos,
           e->text_pos, e->text_len);
    if (e->type == ZIRA_EV_BOOKMARK) printf("%s", e->name ? e->name : "");
    else if (e->type != ZIRA_EV_END) printf("%.*s", (int)e->text_len, c->text + e->text_pos);
    printf("\n");
}

static char *read_file(const char *fn)
{
    FILE *f = fopen(fn, "rb");
    char *b;
    long n;
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    n = ftell(f);
    fseek(f, 0, SEEK_SET);
    b = (char *)malloc((size_t)n + 1);
    if (b) {
        n = (long)fread(b, 1, (size_t)n, f);
        b[n] = 0;
    }
    fclose(f);
    return b;
}

static zira_tts *g_t;
static volatile long g_cancel_at = -1;
static volatile int g_done;
static ctx *g_ctx;

static THREAD_RET canceller(void *arg)
{
    (void)arg;
    for (;;) {
        if (g_done) break;
        if (g_ctx->got >= 16000) {           /* one second of audio has been delivered */
            g_cancel_at = g_ctx->got;
            zira_tts_cancel(g_t);
            break;
        }
        nap(1);
    }
    return 0;
}

int main(int argc, char **argv)
{
    const char *cmd = argc > 1 ? argv[1] : "", *voice = argc > 2 ? argv[2] : "David";
    const char *dir = getenv("ZIRA_DATA"), *emotion = NULL, *text = NULL, *out = NULL;
    int i, first = 3, rate = 0, volume = 100, pitch = 0, flags = 0, xml = -1, rc;
    char err[256];
    zira_callbacks cb;
    ctx c;
    memset(&c, 0, sizeof c);
    if (!strcmp(cmd, "wav")) {
        out = argc > 3 ? argv[3] : NULL;
        first = 4;
    }
    for (i = first; i < argc; i++) {
        if (!strcmp(argv[i], "--data") && i + 1 < argc) dir = argv[++i];
        else if (!strcmp(argv[i], "--rate") && i + 1 < argc) rate = atoi(argv[++i]);
        else if (!strcmp(argv[i], "--volume") && i + 1 < argc) volume = atoi(argv[++i]);
        else if (!strcmp(argv[i], "--pitch") && i + 1 < argc) pitch = atoi(argv[++i]);
        else if (!strcmp(argv[i], "--emotion") && i + 1 < argc) emotion = argv[++i];
        else if (!strcmp(argv[i], "--xml")) xml = 1;
        else if (!strcmp(argv[i], "--no-xml")) xml = 0;
        else if (!text) text = argv[i];
    }
    if (!cmd[0] || (!strcmp(cmd, "wav") && (!out || !text)) || (!strcmp(cmd, "events") && !text)) {
        fprintf(stderr, "usage: lib_test wav|events|cancel|emotions VOICE ...\n");
        return 2;
    }
    if (text && text[0] == '@') {
        char *b = read_file(text + 1);
        if (!b) {
            fprintf(stderr, "cannot read %s\n", text + 1);
            return 2;
        }
        text = b;
        if ((unsigned char)b[0] == 0xef && (unsigned char)b[1] == 0xbb && (unsigned char)b[2] == 0xbf) text += 3;
    }
    /* same default as zira_say.exe and SAPI's SPF_DEFAULT, so the two can be compared byte for byte */
    if (xml < 0) xml = text && strchr(text, '<') != NULL;
    if (xml) flags |= ZIRA_SPEAK_XML;
    g_t = zira_tts_open(dir, voice, err, sizeof err);
    if (!g_t) {
        fprintf(stderr, "lib_test: %s\n", err);
        return 2;
    }
    if (!strcmp(cmd, "emotions")) {
        for (i = 0; zira_tts_emotion_name(g_t, i); i++) printf("%s\n", zira_tts_emotion_name(g_t, i));
        zira_tts_close(g_t);
        return 0;
    }
    zira_tts_set_rate(g_t, rate);
    zira_tts_set_volume(g_t, volume);
    zira_tts_set_pitch(g_t, pitch);
    if (emotion && zira_tts_set_emotion(g_t, emotion)) {
        fprintf(stderr, "lib_test: no emotion \"%s\"\n", emotion);
        zira_tts_close(g_t);
        return 2;
    }
    cb.audio = on_audio;
    cb.event = on_event;
    cb.user = &c;
    if (!strcmp(cmd, "wav")) {
        long pos;
        c.f = fopen(out, "wb");
        if (!c.f) {
            fprintf(stderr, "cannot write %s\n", out);
            return 2;
        }
        fwrite("RIFF\0\0\0\0WAVEfmt ", 1, 16, c.f);
        put(c.f, 16, 4), put(c.f, 1, 2), put(c.f, 1, 2), put(c.f, ZIRA_SAMPLE_RATE, 4), put(c.f, ZIRA_SAMPLE_RATE * 2, 4),
            put(c.f, 2, 2), put(c.f, 16, 2);
        fwrite("data\0\0\0\0", 1, 8, c.f);
        rc = zira_tts_speak(g_t, text, flags, &cb);
        pos = ftell(c.f);
        fseek(c.f, 4, SEEK_SET);
        put(c.f, (unsigned)(pos - 8), 4);
        fseek(c.f, 40, SEEK_SET);
        put(c.f, (unsigned)(pos - 44), 4);
        fclose(c.f);
        zira_tts_close(g_t);
        return rc < 0 ? 1 : 0;
    }
    if (!strcmp(cmd, "events")) {
        c.text = text;
        c.print_events = 1;
        rc = zira_tts_speak(g_t, text, flags, &cb);
        zira_tts_close(g_t);
        return rc < 0 ? 1 : 0;
    }
    if (!strcmp(cmd, "cancel")) {
        static const char *const LONG_TEXT =
            "The quick brown fox jumps over the lazy dog. Pack my box with five dozen liquor jugs. "
            "How vexingly quick daft zebras jump. The five boxing wizards jump quickly. "
            "Sphinx of black quartz, judge my vow. Jackdaws love my big sphinx of quartz. "
            "Bright vixens jump; dozy fowl quack. Quick wafting zephyrs vex bold Jim. "
            "The job requires extra pluck and zeal from every young wage earner.";
        thread_t th;
        long after;
        g_ctx = &c;
        thread_start(&th, canceller, NULL);
        rc = zira_tts_speak(g_t, LONG_TEXT, 0, &cb);
        g_done = 1;
        thread_join(th);
        after = g_cancel_at < 0 ? -1 : c.got - g_cancel_at;
        printf("rc=%d samples=%ld cancel_at=%ld after_cancel=%ld\n", rc, c.got, g_cancel_at, after);
        zira_tts_close(g_t);
        if (rc != 1) { fprintf(stderr, "FAIL: speak returned %d, expected 1 (cancelled)\n", rc); return 1; }
        if (g_cancel_at < 0) { fprintf(stderr, "FAIL: cancel never fired (text too short?)\n"); return 1; }
        if (after > 3200) { fprintf(stderr, "FAIL: %ld samples after cancel (> 2 chunks)\n", after); return 1; }
        /* the other way to stop: the audio callback returns nonzero */
        g_t = zira_tts_open(dir, voice, err, sizeof err);
        memset(&c, 0, sizeof c);
        c.stop_after = 8000;
        cb.user = &c;
        rc = zira_tts_speak(g_t, LONG_TEXT, 0, &cb);
        zira_tts_close(g_t);
        if (rc != 1 || c.got > 8000 + 1600) {
            fprintf(stderr, "FAIL: audio callback stop: rc=%d samples=%ld\n", rc, c.got);
            return 1;
        }
        printf("OK: stopped %ld samples (%.0f ms) after cancel; callback stop at %ld samples\n", after, after / 16.0, c.got);
        return 0;
    }
    fprintf(stderr, "lib_test: unknown command %s\n", cmd);
    zira_tts_close(g_t);
    return 2;
}
