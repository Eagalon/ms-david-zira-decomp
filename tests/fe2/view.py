"""Compact viewer for zftap2 dumps: python view.py dump.txt [line#] [stages]"""
import sys, re
sys.stdout.reconfigure(encoding='utf-8')
path = sys.argv[1]; want = sys.argv[2] if len(sys.argv) > 2 else None
stages = sys.argv[3].split(',') if len(sys.argv) > 3 else ['IN', 'PRO', 'UNIT']
cur = None; st = None
KEYS = ['i88', 'i180', 'i228', 'i244', 'i24c', 'i250', 'i210', 'i214', 'i238', 'i240', 'i254', 'i2b8', 'i2bc', 'i248', 'i22c', 'i230']
for ln in open(path, encoding='utf-8'):
    ln = ln.rstrip('\n')
    if ln.startswith('LINE '):
        cur = ln.split()[1]; st = None
        if want is None or cur == want: print(ln)
        continue
    if want is not None and cur != want: continue
    if ln.startswith('STAGE '): st = ln.split()[1]
    if st not in stages and not ln.startswith(('STAGE', 'U ')): continue
    if ln.startswith('W '):
        f = dict(re.findall(r'(\w+)=(\S*)', ln)); i = ln.split()[1]
        print('  W%-3s %-14s %s pos=%s pron=%s ph=%s pw=%s s=%s fs=%s' % (i, f.get('t'), ' '.join('%s=%s' % (k[1:], f[k]) for k in KEYS),
              f.get('pos'), f.get('pron'), f.get('ph'), f.get('pw'), f.get('s'), (f.get('fs') or '')[18:60]))
    elif ln.startswith(('STAGE', 'SENT', 'PH ', 'IP ', 'QP', 'PS', 'U ')): print(' ', ln[:200])
