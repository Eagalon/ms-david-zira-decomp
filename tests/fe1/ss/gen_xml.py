"""gen_xml.py SRC OUT SEED - wrap random stress lines with SAPI XML tags (enumerator / fragment-boundary tests)."""
import random, sys
r = random.Random(int(sys.argv[3]))
lines = open(sys.argv[1], encoding='utf-8').read().split('\n')[:600]
tags = ['<silence msec="100"/>', '<bookmark mark="b"/>', '<emph>', '</emph>', '<spell>AB</spell>',
        '<context id="address">1 Main St. Apt. 5</context>', '<context id="name">Dr. J. Smith</context>',
        '<context id="date_mdy">1/2/2003</context>', '<rate speed="2">', '</rate>', '<pron sym="h eh 1 l ow"/>',
        '<volume level="50">', '</volume>', '<partofsp part="noun">read.</partofsp>']
BS = chr(92)
out = []
for l in lines:
    for a, b in ((BS + 'n', ' '), (BS + 't', ' '), (BS + 'r', ' '), (BS, '/'), ('&', 'and'), ('<', '('), ('>', ')')):
        l = l.replace(a, b)
    w = l.split(' ')
    for k in range(r.randint(1, 4)):
        w.insert(r.randint(0, len(w)), r.choice(tags))
    out.append(' '.join(w))
open(sys.argv[2], 'w', encoding='utf-8').write('\n'.join(out) + '\n')
