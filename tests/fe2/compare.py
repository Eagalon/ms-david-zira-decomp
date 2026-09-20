"""compare.py - zf2 vs the real engine, feature matrix field by field.

usage: python compare.py <voice> [corpus.txt] [--rerun] [--show N] [--line K]
  voice   david | zira | mark
  corpus  default tests/fe2/corpus.txt
Runs harness/zftap2.exe (engine dump, cached in tests/fe2/out/<voice>.dump unless --rerun) and
build/fe2/zf2_t_dump.exe (zf2 fed with the dump's stage-IN tree), then compares every FX matrix (one per sentence).
"""
import os, re, subprocess, sys, collections
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
VOICES = {'david': 'David', 'zira': 'Zira', 'mark': 'Mark'}
VDIR = 'C:/Windows/Speech_OneCore/Engines/TTS/en-US/M1033'

def parse(path, tag):
    """-> {line: [matrix, ...]}, matrix = list of rows, row = list of 'k:v' / 'N'"""
    out = collections.OrderedDict(); texts = {}
    cur = None; mat = None; want = 0
    for ln in open(path, encoding='utf-8', errors='replace'):
        ln = ln.rstrip('\r\n')
        if ln.startswith('LINE '):
            parts = ln.split(' ', 2); cur = int(parts[1]); texts[cur] = parts[2] if len(parts) > 2 else ''
            out.setdefault(cur, []); want = 0; continue
        m = re.match(tag + r' (\d+)', ln)
        if m:
            n = int(m.group(1))
            if n > 1: mat = []; out[cur].append(mat); want = n
            else: want = 0
            continue
        if want and ln.startswith('F '):
            vals = ln.split(':', 1)[1].split() if ':' in ln else []
            # engine rows: "F i prop=.. cnt=..: v v"; mine: "F i cnt=..: v v"
            head, _, rest = ln.partition(': ')
            vals = rest.split() if rest else []
            if head.endswith('cnt=0:'): vals = []
            mat.append(vals); want -= 1
    return out, texts

def main():
    a = sys.argv[1:]
    voice = a[0].lower(); V = VOICES[voice]
    corpus = next((x for x in a[1:] if not x.startswith('--') and not x.isdigit()), os.path.join(ROOT, 'tests', 'fe2', 'corpus.txt'))
    show = int(a[a.index('--show') + 1]) if '--show' in a else 10
    only = int(a[a.index('--line') + 1]) if '--line' in a else None
    outdir = os.path.join(ROOT, 'tests', 'fe2', 'out'); os.makedirs(outdir, exist_ok=True)
    base = os.path.basename(os.path.dirname(os.path.abspath(corpus))) + '_' + os.path.splitext(os.path.basename(corpus))[0]
    edump = os.path.join(outdir, '%s_%s.dump' % (base, voice)); mine = os.path.join(outdir, '%s_%s.zf2' % (base, voice))
    if '--rerun' in a or not os.path.exists(edump):
        subprocess.run([os.path.join(ROOT, 'harness', 'zftap2.exe'), voice, '@' + corpus, edump, 'nowave'], check=True)
    with open(mine, 'w', encoding='utf-8') as f:
        # own voice first; the others are used for sentences the engine rendered with another voice (<lang>)
        args = [os.path.join(ROOT, 'build', 'fe2', 'zf2_t_dump.exe')]
        for W in [V] + [x for x in VOICES.values() if x != V]:
            args += [VDIR + W, os.path.join(ROOT, 'tests', 'fe2', 'feat_%s.txt' % W)]
        subprocess.run(args + [edump], stdout=f, check=True)
    feats = [l.strip() for l in open(os.path.join(ROOT, 'tests', 'fe2', 'feat_%s.txt' % V)) if l.strip()]
    featsof = {len(x): x for x in ([l.strip() for l in open(os.path.join(ROOT, 'tests', 'fe2', 'feat_%s.txt' % W)) if l.strip()]
                                   for W in VOICES.values())}
    E, texts = parse(edump, 'FX'); M, _ = parse(mine, 'MYFX')
    nlines = nok = ncell = ncellbad = 0; badfeat = collections.Counter(); shown = 0; badlines = []
    for ln, emats in E.items():
        if only is not None and ln != only: continue
        mmats = M.get(ln, []); nlines += 1; ok = True
        if len(emats) != len(mmats):
            ok = False; badfeat['#utterances'] += 1
        for u, (em, mm) in enumerate(zip(emats, mmats)):
            feats = featsof.get(len(em), feats)
            if len(em) != len(mm): ok = False; badfeat['#features'] += 1
            for fi, (er, mr) in enumerate(zip(em, mm)):
                ncell += len(er)
                if er != mr:
                    ok = False; badfeat[feats[fi] if fi < len(feats) else fi] += 1
                    nb = sum(1 for x, y in zip(er, mr) if x != y) + abs(len(er) - len(mr)); ncellbad += nb
                    if shown < show:
                        shown += 1
                        print('line %d utt %d f%d %s\n  %s\n  eng  %s\n  zf2  %s' % (ln, u, fi, feats[fi] if fi < len(feats) else '?',
                              texts.get(ln, '')[:150], ' '.join(er), ' '.join(mr)))
        if ok: nok += 1
        else: badlines.append(ln)
    print('%s: %d/%d lines match exactly; cells %d, mismatching %d' % (voice, nok, nlines, ncell, ncellbad))
    for k, v in badfeat.most_common(20): print('  %5d  %s' % (v, k))
    if badlines: print('bad lines:', ' '.join(map(str, badlines[:80])))

if __name__ == '__main__':
    main()
