"""Tests for the host library (src/zira_tts.h, built as build/<arch>/zira.exe + zira_lib_test.exe).

  python tests/lib/run.py [corpus] [voices...]

1. identity: for every corpus line and every voice the library must produce byte-identical audio to
   zira_say.exe (which is what tests/e2e/bulk.py checks bit-exact against the real engine), with neutral
   settings and with --rate/--volume/--pitch/--emotion set.
2. events: sentence/word/bookmark offsets must point at the right bytes of the UTF-8 input, in order, with
   non-decreasing audio positions.
3. cancel: zira_tts_cancel from another thread stops within a chunk (zira_lib_test cancel).
"""
import os, subprocess, sys, wave

Z = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
BIN = os.path.join(Z, "build", "x64")
SAY = os.path.join(BIN, "zira_say.exe")
LIB = os.path.join(BIN, "zira_lib_test.exe")
TMP = os.path.join(Z, "tests", "lib", "tmp")
os.makedirs(TMP, exist_ok=True)


def pcm(path):
    with wave.open(path) as w:
        return w.readframes(w.getnframes())


def run(cmd):
    return subprocess.run(cmd, capture_output=True, text=True, encoding="utf-8", errors="replace")


def identity(lines, voices, opts, label):
    bad = 0
    t = os.path.join(TMP, "line.txt")
    a, b = os.path.join(TMP, "say.wav"), os.path.join(TMP, "lib.wav")
    for voice in voices:
        for i, line in enumerate(lines):
            open(t, "w", encoding="utf-8").write(line)
            run([SAY, "--voice", voice] + opts + ["@" + t, a])
            run([LIB, "wav", voice, b] + opts + ["@" + t])
            try:
                same = pcm(a) == pcm(b)
            except Exception:
                same = False
            if not same:
                bad += 1
                if bad < 6:
                    print("  MISMATCH %s line %d: %s" % (voice, i + 1, line[:60]))
    n = len(lines) * len(voices)
    print("%-28s %d/%d identical to zira_say" % (label, n - bad, n))
    return bad == 0


def events(voice):
    text = 'One two three. Four <bookmark mark="mid"/>five six.'
    r = run([LIB, "events", voice, "--xml", text])
    rows = [l.split("|", 4) for l in r.stdout.splitlines() if "|" in l]
    ok, prev = True, -1
    words = []
    for kind, pos, off, ln, body in rows:
        pos, off, ln = int(pos), int(off), int(ln)
        if pos < prev:
            print("  events: audio position went backwards at %s %r" % (kind, body))
            ok = False
        prev = pos
        if kind in ("sentence", "word") and text[off:off + ln] != body:
            print("  events: %s offset %d..%d is %r, event says %r" % (kind, off, off + ln, text[off:off + ln], body))
            ok = False
        if kind == "word":
            words.append(body)
    want = ["One", "two", "three", "Four", "five", "six"]
    if words != want:
        print("  events: words %r != %r" % (words, want))
        ok = False
    if not any(k == "bookmark" and b == "mid" for k, _, _, _, b in rows):
        print("  events: bookmark 'mid' missing")
        ok = False
    if not rows or rows[-1][0] != "end":
        print("  events: no end event")
        ok = False
    print("%-28s %s" % ("events (%s)" % voice, "ok" if ok else "FAILED"))
    return ok


def cancel(voice):
    r = run([LIB, "cancel", voice])
    print("%-28s %s" % ("cancel (%s)" % voice, r.stdout.strip().splitlines()[-1] if r.stdout.strip() else r.stderr.strip()))
    return r.returncode == 0


if __name__ == "__main__":
    corpus = sys.argv[1] if len(sys.argv) > 1 else os.path.join(Z, "tests", "fe1", "corpus.txt")
    voices = sys.argv[2:] or ["David", "Zira", "Mark"]
    lines = [l.rstrip("\r\n") for l in open(corpus, encoding="utf-8-sig")]
    lines = [l for l in lines if l.strip() and not l.startswith("##")]
    good = True
    good &= identity(lines, voices, [], "neutral, whole corpus")
    short = lines[:40]
    good &= identity(short, voices, ["--rate", "4"], "rate 4")
    good &= identity(short, voices, ["--rate", "-6", "--volume", "60"], "rate -6, volume 60")
    good &= identity(short, voices, ["--emotion", "happy"], "emotion happy")
    good &= identity(short, voices, ["--emotion", "sad"], "emotion sad")
    good &= identity(short, voices, ["--emotion", "angry"], "emotion angry")
    for v in voices:
        good &= events(v)
        good &= cancel(v)
    print("ALL OK" if good else "FAILURES")
    sys.exit(0 if good else 1)
