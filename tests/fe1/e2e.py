"""e2e.py <voice> [corpus] - text -> zf1 -> zf2 feature matrices vs the real engine (harness/zftap2 dump,
cached by tests/fe2/compare.py in tests/fe2/out/<corpusdir>_<corpus>_<voice>.dump).
Uses build/zf1_t_e2e.exe (src/zf1_t_e2e.c).  Reports lines whose matrices are all identical."""
import os, sys, subprocess, importlib.util
ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
spec = importlib.util.spec_from_file_location('c2', os.path.join(ROOT, 'tests', 'fe2', 'compare.py'))
c2 = importlib.util.module_from_spec(spec); spec.loader.exec_module(c2)
voice = sys.argv[1].lower(); V = c2.VOICES[voice]
corpus = sys.argv[2] if len(sys.argv) > 2 else os.path.join(ROOT, 'tests', 'fe1', 'corpus.txt')
base = os.path.basename(os.path.dirname(os.path.abspath(corpus))) + '_' + os.path.splitext(os.path.basename(corpus))[0]
edump = os.path.join(ROOT, 'tests', 'fe2', 'out', '%s_%s.dump' % (base, voice))
if not os.path.exists(edump):
    subprocess.run([os.path.join(ROOT, 'harness', 'zftap2.exe'), voice, '@' + corpus, edump, 'nowave'], check=True)
mine = os.path.join(ROOT, 'tests', 'fe1', 'e2e_%s_%s.out' % (base, voice))
with open(mine, 'w', encoding='utf-8') as f:
    subprocess.run([os.path.join(ROOT, 'build', 'zf1_t_e2e.exe'), c2.VDIR + V,
                    os.path.join(ROOT, 'tests', 'fe2', 'feat_%s.txt' % V), corpus], stdout=f, check=True)
E, texts = c2.parse(edump, 'FX'); M, _ = c2.parse(mine, 'MYFX')
ok = 0; bad = []
for ln, em in E.items():
    if em == M.get(ln, []): ok += 1
    else: bad.append(ln)
print('%s e2e: %d/%d lines identical feature matrices' % (voice, ok, len(E)))
if bad: print('bad lines:', ' '.join(map(str, bad[:100])))
