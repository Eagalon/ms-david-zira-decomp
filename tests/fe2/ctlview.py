"""print word/phone ctl blocks of the UNIT stage for lines matching a regex: python ctlview.py dump regex"""
import sys, re
sys.stdout.reconfigure(encoding='utf-8')
path, pat = sys.argv[1], re.compile(sys.argv[2])
show = False; st = None; words = {}
for ln in open(path, encoding='utf-8'):
    ln = ln.rstrip('\n')
    if ln.startswith('LINE '): show = bool(pat.search(ln)); st = None
    if not show: continue
    if ln.startswith('LINE ') or ln.startswith('U '): print(ln)
    if ln.startswith('STAGE '): st = ln.split()[1]; words = {}
    if st != 'UNIT': continue
    if ln.startswith('W '):
        f = dict(re.findall(r'(\w+)=(\S*)', ln)); words[ln.split()[1]] = f
        print('  W%s %s bi=%s pc=%s 210=%s fs=%s fpr=%s' % (ln.split()[1], f.get('t'), f.get('i244'), f.get('i250'), f.get('i210'), (f.get('fs') or '')[17:60], f.get('fpr')))
    if ln.startswith('Y '):
        f = dict(re.findall(r'(\w+)=(\S*)', ln)); print('    Y w=%s' % f['w'], end='')
    if ln.startswith('H '):
        f = dict(re.findall(r'(\w+)=(\S*)', ln)); print('   H%s %s %s' % (ln.split()[1], f['n'], f.get('ctl')))
