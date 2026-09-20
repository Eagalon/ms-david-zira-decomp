"""replay.py DUMP - replay every CSentSepImpl call logged by harness/zftap1_ss.exe in Speak mode ("SS c h len=N
in="..." next=X" lines, i.e. the calls made by the real CSentenceEnumerator) through build/zf1_t_ss.exe and compare
consumed length + hard-end flag."""
import re, sys, os, subprocess
sys.stdout.reconfigure(encoding='utf-8', errors='backslashreplace')
HERE = os.path.dirname(os.path.abspath(__file__))
EXE = os.path.join(HERE, '..', '..', '..', 'build', 'zf1_t_ss.exe')


def unesc(s):
    return re.sub(r'\\x([0-9a-f]{2})', lambda m: chr(int(m.group(1), 16)), s)


def esc(s):
    o = []
    for ch in s:
        c = ord(ch)
        if ch == '\\': o.append('\\\\')
        elif c < 0x20 or c == 0x7f or 0xd800 <= c < 0xe000: o.append('\\u%04x' % c)
        else: o.append(ch)
    return ''.join(o)


calls = []
for l in open(sys.argv[1], encoding='utf-8', errors='surrogateescape'):
    m = re.match(r'SS (-?\d+) (-?\d+) len=(\d+) in="(.*)" next=(\d+)$', l.rstrip('\n'))
    if m:
        txt = unesc(m.group(4))
        calls.append((int(m.group(1)), int(m.group(2)), int(m.group(5)), txt))
inp = os.path.join(HERE, 'replay_in.txt')
with open(inp, 'w', encoding='utf-8', errors='surrogatepass') as f:
    for c, h, nx, t in calls:
        f.write('%d\t%s\n' % (nx, esc(t)))
outp = os.path.join(HERE, 'replay_out.txt')
subprocess.run([EXE, inp, outp, 'replay'], check=True)
got = [l.split() for l in open(outp, encoding='utf-8') if l.startswith('SS')]
bad = 0
for (c, h, nx, t), g in zip(calls, got):
    if [str(c), str(h)] != g[1:3]:
        bad += 1
        if bad <= 15: print('E %d %d P %s %s next=%d in=%r' % (c, h, g[1], g[2], nx, t[:120]))
print('%d/%d calls identical' % (len(calls) - bad, len(calls)))
