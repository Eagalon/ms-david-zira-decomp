"""enumtest.py DUMP CORPUS - test zf1_ss_next (CSentenceEnumerator piece loop) against the SN lines logged by
harness/zftap1_ss.exe (Speak mode).  Engine fragment nodes are rebuilt from the logged SAPI fragments (F lines):
SAPI action 6 (unknown tag) is dropped, actions > 5 become 8, U+200B is removed from speak/spell text, say-as
fragments are trimmed of ASCII blanks; the character after each fragment (text[len]) is taken from the corpus line
(0 at the end / after a U+200B copy)."""
import re, sys, os, subprocess
sys.stdout.reconfigure(encoding='utf-8', errors='backslashreplace')
HERE = os.path.dirname(os.path.abspath(__file__))
EXE = os.path.join(HERE, '..', '..', '..', 'build', 'zf1_t_ss.exe')


def unesc(s):
    return re.sub(r'\\x([0-9a-f]{2})', lambda m: chr(int(m.group(1), 16)), s)


def esc(s):
    return ''.join('\\u%04x' % ord(c) if (ord(c) < 0x20 or c == '\\' or ord(c) == 0x7f) else c for c in s)


blocks = []
cur = None
for l in open(sys.argv[1], encoding='utf-8', errors='surrogateescape'):
    l = l.rstrip('\n')
    if l.startswith('L '):
        no, _, text = l[2:].partition('\t')
        cur = {'no': int(no), 'text': unesc(text), 'F': [], 'SN': []}
        blocks.append(cur)
    elif cur is None:
        continue
    elif l.startswith('F '):
        if cur['SN']:   # a new Speak call inside the same corpus line (<voice>/<lang> split): new block
            cur = {'no': cur['no'] * 100 + len([b for b in blocks if b['no'] // 100 == cur['no']]) + 1 if cur['no'] < 100000 else cur['no'] + 1, 'text': cur['text'], 'F': [], 'SN': []}
            blocks.append(cur)
        m = re.match(r'F act=(\d+) .* cat=(.*?) before=.* off=(\d+) len=(\d+) "(.*)"$', l)
        cur['F'].append((int(m.group(1)), m.group(2), int(m.group(3)), int(m.group(4)), unesc(m.group(5))))
    elif l.startswith('SN'):
        cur['SN'].append(l)
inp = os.path.join(HERE, 'enum_in.txt')
with open(inp, 'w', encoding='utf-8', errors='surrogatepass') as f:
    for b in blocks:
        f.write('L %d\n' % b['no'])
        for act, cat, off, ln, text in b['F']:
            if act == 6:
                continue
            nact = act if act <= 5 else 8
            nxt = b['text'][off + ln] if off + ln < len(b['text']) else '\0'
            t = text
            if nact in (0, 4) and '​' in t:
                t = t.replace('​', '')
                nxt = '\0'
            if cat != '-':
                a, e = 0, len(t)
                while a < e and t[a] in ' \t\r\n\x0b\x0c': a += 1
                while e > a and t[e - 1] in ' \t\r\n\x0b\x0c': e -= 1
                if e < len(t): nxt = t[e]
                t = t[a:e]
            f.write('F %d %d %s %s\n' % (nact, ord(nxt), cat if cat != '-' else '-', esc(t)))
        f.write('E\n')
outp = os.path.join(HERE, 'enum_out.txt')
subprocess.run([EXE, inp, outp, 'enum'], check=True)
got = {}
k = None
for l in open(outp, encoding='utf-8'):
    l = l.rstrip('\n')
    if l.startswith('L '): k = int(l[2:]); got[k] = []
    elif l.startswith('SN'): got[k].append(l)
blocks = [b for b in blocks if b['F']]   # lines SAPI rejected (bad XML) never reach the engine
bad = 0
for b in blocks:
    if b['SN'] != got.get(b['no']):
        bad += 1
        if bad <= 15: print('L', b['no'], b['text'][:100], '\n  E', b['SN'], '\n  P', got.get(b['no']))
print('%d/%d lines identical (%d sentences)' % (len(blocks) - bad, len(blocks), sum(len(b['SN']) for b in blocks)))
