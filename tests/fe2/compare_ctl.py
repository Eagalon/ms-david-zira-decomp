"""compare_ctl.py <voice> [corpus] : per-phone prosody block (phone+0x78: volume, rate, pitch, range, pitch factor,
group ms, pause ms) of zf2 vs the engine (stage UNIT "H ... ctl=" lines).  Uses the dumps made by compare.py."""
import os, sys, collections
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
voice = sys.argv[1]
corpus = sys.argv[2] if len(sys.argv) > 2 else os.path.join(ROOT, 'tests', 'fe2', 'corpus.txt')
base = os.path.basename(os.path.dirname(os.path.abspath(corpus))) + '_' + os.path.splitext(os.path.basename(corpus))[0]
out = os.path.join(ROOT, 'tests', 'fe2', 'out')
def eng(path):
    res = collections.OrderedDict(); cur = None; st = None; utt = None
    for ln in open(path, encoding='utf-8', errors='replace'):
        if ln.startswith('LINE '): cur = int(ln.split()[1]); res[cur] = []; continue
        if ln.startswith('STAGE '): st = ln.split()[1]
        if ln.startswith('STAGE UNIT'): utt = []; res[cur].append(utt)
        if st == 'UNIT' and ln.startswith('H ') and 'ctl=' in ln:
            utt.append(','.join(ln.split('ctl=')[1].split()[0].split(',')[:7]))
    return res
def mine(path):
    res = collections.OrderedDict(); cur = None; utt = None
    for ln in open(path, encoding='utf-8', errors='replace'):
        if ln.startswith('LINE '): cur = int(ln.split()[1]); res[cur] = []; continue
        if ln.startswith('MYFX'): utt = []; res[cur].append(utt)
        if ln.startswith('CTL '): utt.append(ln.split()[2])
    return res
E = eng(os.path.join(out, '%s_%s.dump' % (base, voice))); M = mine(os.path.join(out, '%s_%s.zf2' % (base, voice)))
ok = n = 0; shown = 0
for ln, eu in E.items():
    n += 1; mu = M.get(ln, [])
    if eu == mu: ok += 1; continue
    if shown < 5:
        shown += 1
        for a, b in zip(eu, mu):
            if a != b: print('line', ln, '\n eng', a[:12], '\n zf2', b[:12]); break
        else: print('line', ln, 'utterance count', len(eu), len(mu))
print('%s ctl: %d/%d lines match' % (voice, ok, n))
