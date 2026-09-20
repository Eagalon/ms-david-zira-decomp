"""wbtest.py DUMP - compare zf1_wb (build/zf1_t_wb.exe) with the engine's CWhiteSpaceBreaker (WB lines of a
zftap1 'hooks' dump)."""
import re, subprocess, sys, os
sys.stdout.reconfigure(encoding='utf-8', errors='backslashreplace')
HERE = os.path.dirname(os.path.abspath(__file__))
EXE = os.path.join(HERE, '..', '..', '..', 'build', 'zf1_t_wb.exe')


def unesc(s):
    return re.sub(r'\\x([0-9a-f]{2})', lambda m: chr(int(m.group(1), 16)), s)


cases = []
for l in open(sys.argv[1], encoding='utf-8', errors='surrogateescape'):
    m = re.match(r'WB flag=(\d) in="(.*)" out=(.*)$', l.rstrip('\n'))
    if m:
        toks = re.findall(r'"((?:[^"\\]|\\.)*)"', m.group(3))
        cases.append((m.group(1), unesc(m.group(2)), [unesc(t) for t in toks]))
inp = os.path.join(HERE, 'wbin.txt')
open(inp, 'w', encoding='utf-8', errors='surrogatepass').write(''.join('%s\t%s\n' % (f, t) for f, t, _ in cases))
out = subprocess.run([EXE, inp], capture_output=True).stdout.decode('utf-8', 'surrogatepass').split('\n')
bad = 0
for (f, t, exp), got in zip(cases, out):
    if '|'.join(exp) != got.rstrip('\r'):
        bad += 1
        if bad <= 15:
            print('IN ', t, '\n  E', '|'.join(exp), '\n  P', got)
print('%d/%d identical' % (len(cases) - bad, len(cases)))
