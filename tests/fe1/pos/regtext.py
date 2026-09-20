#!/usr/bin/env python3
"""regtext.py DUMP : list words whose RegularText (sb8) differs from lower(Text)"""
import re, sys, collections
sys.stdout.reconfigure(encoding='utf-8')
TOK = re.compile(r'(\w+)=("(?:[^"\\]|\\.)*"|\[[^\]]*\]|\S+)')
n = 0
c = collections.Counter()
for l in open(sys.argv[1], encoding='utf-8'):
    if l.startswith('W '):
        d = dict(TOK.findall(l[2:]))
        t = d.get('text', '""')[1:-1]; r = d.get('sb8', '""')[1:-1]
        if r != t.lower():
            n += 1
            c[(t, r, d['pos'])] += 1
for k, v in c.most_common(60): print(v, k)
print(n)
