#!/usr/bin/env python3
"""ptconv.py DUMP OUT : extract PTIN/PTOUT node chains from a zftap1_pos dump into a simple test file.
Per chain: 'C n' then n lines 'pos kind c1,c2 l1,l2 outpos hextext'."""
import sys, re
NODE = re.compile(r'\["((?:[^"\\]|\\.)*)" p(\d+) k(\d+) c([\d,]*) l([\d,]*)\]')


def unesc(s):
    return re.sub(r'\\x([0-9a-f]{2})', lambda m: chr(int(m.group(1), 16)), s)


out = open(sys.argv[2], 'w')
pin = None
WNODE = re.compile(r'\["((?:[^"\\]|\\.)*)" t(\d+) p(\d+)\]')
tin = None
for l in open(sys.argv[1], encoding='utf-8', errors='replace'):
    if l.startswith('TAGIN'):
        tin = WNODE.findall(l)
    elif l.startswith('TAGOUT') and tin is not None:
        to = WNODE.findall(l)
        out.write('T %d\n' % len(tin))
        for a, b in zip(tin, to):
            t = unesc(a[0]).encode('utf-16le').hex() or '-'
            out.write('%s %s %s %s\n' % (a[1], a[2], b[2], t))
        tin = None
    elif l.startswith('PTIN'):
        pin = NODE.findall(l)
    elif l.startswith('PTOUT') and pin is not None:
        po = NODE.findall(l)
        out.write('C %d\n' % len(pin))
        for a, b in zip(pin, po):
            t = unesc(a[0]).encode('utf-16le').hex() or '-'
            out.write('%s %s %s %s %s %s\n' % (a[1], a[2], a[3] or '-', a[4] or '-', b[1], t))
        pin = None

# oracle of container lexicon lookups (LEX8 lines) -> OUT.lex
if len(sys.argv) > 2:
    LEX = re.compile(r'^LEX8 ra=\w+ hr=(\w+) "((?:[^"\\]|\\.)*)"(?: A(.*))?')
    seen = {}
    for l in open(sys.argv[1], encoding='utf-8', errors='replace'):
        m = LEX.match(l.rstrip('\n'))
        if m:
            at = ''.join(x + ';' for x in re.findall(r'\[([\d,]*)\]', m.group(3) or ''))
            seen[unesc(m.group(2)).encode('utf-16le').hex()] = (1 if m.group(1) == '00000000' else 0, at or '-')
    with open(sys.argv[2] + '.lex', 'w') as f:
        for k, (v, at) in seen.items():
            if k: f.write('%d %s %s\n' % (v, k, at))
