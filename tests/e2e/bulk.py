"""bulk.py VOICE CORPUS: speak every line with the real OneCore engine (harness/ziraprobe) and with
build/x64/zira_say, compare the WAVs. Writes tests/e2e/<voice>_<corpus>.txt with the mismatches."""
import os, subprocess, sys, wave
import numpy as np
Z = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
voice, corpus = sys.argv[1], sys.argv[2]
tok = r"HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech_OneCore\Voices\Tokens\MSTTS_V110_enUS_%sM" % voice
tmp = os.path.join(Z, "tests", "e2e", "tmp_" + voice); os.makedirs(tmp, exist_ok=True)
def load(f):
    w = wave.open(f); return np.frombuffer(w.readframes(w.getnframes()), np.int16).astype(np.int64)
lines = [l.rstrip("\r\n") for l in open(corpus, encoding="utf-8-sig")]
ok = bad = 0; report = []
for i, line in enumerate(lines):
    if not line.strip() or line.startswith("##"): continue
    r, c, t = os.path.join(tmp, "r.wav"), os.path.join(tmp, "c.wav"), os.path.join(tmp, "l.txt")
    open(t, "w", encoding="utf-8").write(line)
    subprocess.run([os.path.join(Z, "harness", "ziraprobe.exe"), line, r, tok], capture_output=True)
    subprocess.run([os.path.join(Z, "build", "x64", "zira_say.exe"), "--voice", voice, "@" + t, c], capture_output=True)
    try:
        a, b = load(c), load(r)
        n = min(len(a), len(b)); same = len(a) == len(b) and np.array_equal(a, b)
    except Exception as e:
        same = False; a = b = np.zeros(0); n = 0
    if same: ok += 1
    else:
        bad += 1
        d = a[:n] - b[:n]; nz = np.nonzero(d)[0]
        report.append("line %d: len %d vs %d, first diff %s | %s" % (i + 1, len(a), len(b), nz[:1], line))
out = os.path.join(Z, "tests", "e2e", "%s_%s.txt" % (voice, os.path.splitext(os.path.basename(corpus))[0]))
open(out, "w", encoding="utf-8").write("\n".join(report + ["%s: %d/%d exact" % (voice, ok, ok + bad)]))
print("%s: %d/%d exact" % (voice, ok, ok + bad))
