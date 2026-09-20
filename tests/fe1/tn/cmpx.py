#!/usr/bin/env python3
"""cmpx.py: compare the TN-produced words (i27c=1) of the engine dump (../david.dump) with zf1_t_tn X-mode output
(qx.c.out, lines listed in qx.map)."""
import re, sys
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
TOK = re.compile(r'(\w+)=("(?:[^"\\]|\\.)*"|\S+)')
F = ['text', 'i214', 'i248', 'i270', 'i274', 's188', 's1b0']
dump = sys.argv[1] if len(sys.argv) > 1 else '../david.dump'
eng = {}
cur = None
for l in open(dump, encoding='utf-8'):
    if l.startswith('L '):
        cur = int(l[2:].split('\t')[0]); eng[cur] = []
    elif l.startswith('W ') and cur is not None:
        d = dict(TOK.findall(l))
        if d.get('i27c') == '1':
            eng[cur].append(tuple(d.get(k, '""').strip('"') for k in F))
nums = [int(x) for x in open('qx.map').read().split()]
mine = []
c = None
for l in open('qx.c.out', encoding='utf-8'):
    if l.startswith('Q '):
        c = []; mine.append(c)
    elif l.startswith('W '):
        d = dict(TOK.findall(l)); c.append(tuple(d.get(k, '""').strip('"') for k in F))
bad = 0
for n, m in zip(nums, mine):
    e = eng.get(n, [])
    if e != m:
        bad += 1
        if bad <= 20:
            print('L', n)
            for i in range(max(len(e), len(m))):
                a = e[i] if i < len(e) else None
                b = m[i] if i < len(m) else None
                if a != b:
                    print('   E', a); print('   C', b)
print('bad', bad, 'of', len(nums))
