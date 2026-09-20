"""compare_ev.py <voice> : SAPI events of zf2 vs the engine.
Engine events come from tests/fe2/out/wave_<voice>.dump (zftap2 without 'nowave'); zf2 events from a zf2_t_dump run
on that dump.  Compared per Speak line, in order: id, wParam (PHONEME/VISEME: low 16 bits = next id; the high word is
the duration, filled by the backend), lParam (BOOKMARK: the name).  Also checks that events zf2 attaches to the
same phone share one audio offset in the engine and that offsets never decrease."""
import os, sys, subprocess, collections
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
VOICES = {'david': 'David', 'zira': 'Zira', 'mark': 'Mark'}
VDIR = 'C:/Windows/Speech_OneCore/Engines/TTS/en-US/M1033'
voice = sys.argv[1]; V = VOICES[voice]
dump = sys.argv[2] if len(sys.argv) > 2 else os.path.join(ROOT, 'tests', 'fe2', 'out', 'wave_%s.dump' % voice)
mine = dump + '.zf2'
args = [os.path.join(ROOT, 'build', 'fe2', 'zf2_t_dump.exe')]
for W in [V] + [x for x in VOICES.values() if x != V]:
    args += [VDIR + W, os.path.join(ROOT, 'tests', 'fe2', 'feat_%s.txt' % W)]
with open(mine, 'w', encoding='utf-8') as f: subprocess.run(args + [dump], stdout=f, check=True)
def key(i, w, l, s):
    if i in (6, 8): w &= 0xffff
    return (i, w, s if i == 4 else l)
E = collections.OrderedDict(); T = {}; cur = None
for ln in open(dump, encoding='utf-8', errors='replace'):
    if ln.startswith('LINE '): p = ln.rstrip('\n').split(' ', 2); cur = int(p[1]); T[cur] = p[2] if len(p) > 2 else ''; E[cur] = []; continue
    if ln.startswith('EV '):
        p = ln.split(); E[cur].append((key(int(p[1]), int(p[2]), int(p[3]), p[5] if len(p) > 5 else None), int(p[4])))
M = collections.OrderedDict(); cur = None; base = 0
for ln in open(mine, encoding='utf-8', errors='replace'):
    if ln.startswith('LINE '): cur = int(ln.split()[1]); M[cur] = []; base = 0; continue
    if ln.startswith('MYFX'): base = len(M[cur]) and (max(x[1] for x in M[cur]) + 1000000)
    if ln.startswith('MYEV '):
        p = ln.split(); M[cur].append((key(int(p[1]), int(p[2]), int(p[3]), p[5] if len(p) > 5 else None), base + int(p[4])))
ok = n = bad_off = 0; shown = 0
for ln, ev in E.items():
    n += 1; mv = M.get(ln, [])
    good = [a[0] for a in ev] == [b[0] for b in mv]
    if good:  # offsets: same zf2 phone -> same engine offset, non-decreasing
        seen = {}
        for (k1, off), (k2, ph) in zip(ev, mv):
            if ph in seen and seen[ph] != off: good = False; bad_off += 1; break
            seen[ph] = off
        offs = [o for _, o in ev]
        if offs != sorted(offs): good = False
    if good: ok += 1
    elif shown < 6:
        shown += 1
        print('line %d %s' % (ln, T[ln][:120]))
        for i, (a, b) in enumerate(zip(ev + [(None, 0)] * 3, mv + [(None, 0)] * 3)):
            if a[0] != b[0] or i > 200: print('  at %d: eng %s  zf2 %s' % (i, ev[i:i + 4], mv[i:i + 4])); break
print('%s events: %d/%d lines match (offset-grouping failures %d)' % (voice, ok, n, bad_off))
