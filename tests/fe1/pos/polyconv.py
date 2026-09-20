#!/usr/bin/env python3
"""polyconv.py DUMP OUT : sentences of a zftap1_pos dump -> test input for zf1_t_poly.
Per sentence: 'S n', then per word one line of space separated fields:
  type pos action i278 srcoff srclen cur nprons prons ci_hex text_hex ne_hex f320 prevchars_hex nextchars_hex
prons = '.'-joined hex u16 strings joined by ',' ('-' if none).  Hex strings '-' when empty.
The state is the FINAL (zf1 boundary) state; the test resets what CPolyphony/CRF changed."""
import sys, re

TOK = re.compile(r'(\w+)=("(?:[^"\\]|\\.)*"|\[[^\]]*\]|\S+)')


def unesc(s):
    return re.sub(r'\\x([0-9a-f]{2})', lambda m: chr(int(m.group(1), 16)), s)


def hx(s):
    return s.encode('utf-16le').hex() if s else '-'


out = open(sys.argv[2], 'w')
sent = None


def flush():
    if sent is None: return
    out.write('S %d\n' % len(sent))
    for l in sent: out.write(l + '\n')


for raw in open(sys.argv[1], encoding='utf-8', errors='replace'):
    raw = raw.rstrip('\n')
    if raw.startswith('L '):
        flush(); sent = None
        out.write('L %s\n' % raw[2:].split('\t')[0])
    elif raw.startswith('S '):
        flush(); sent = []
    elif raw.startswith('W ') and sent is not None:
        d = dict(TOK.findall(raw[2:]))
        g = lambda k: unesc(d[k][1:-1]) if k in d else ''
        prons = d.get('prons')
        cur = -1; plist = []
        if prons:
            items = prons[1:-1].split('|') if prons != '[]' else []
            for i, it in enumerate(items):
                if it.startswith('*'): cur = i; it = it[1:]
                plist.append('' if it == '(null)' else unesc(it))
        ps = ','.join('.'.join('%x' % ord(c) for c in p) or 'x' for p in plist) or '-'
        fs = d.get('fs', '0').split(',')
        sent.append(' '.join(str(x) for x in [d['i88'], d['pos'], fs[0], d['i278'], d['i270'], d['i274'], cur,
                                               len(plist), ps, hx(g('sd8')), hx(g('text')), hx(g('s188')),
                                               d.get('f320', '1'), hx(g('sf8')), hx(g('s118')), hx(g('sb8'))]))
flush()
