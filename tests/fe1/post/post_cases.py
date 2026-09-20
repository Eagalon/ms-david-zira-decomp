"""post_cases.py DUMP [DUMP...] - build zf1_t_post input from zftap1_post dumps, run it and compare.

Cases:
  W9   = Analyze step 9 (pre-step9 word list -> post-step9 type/i180)
  SENT = post-Analyze steps (pre-vtb0 sentence words -> sentence type, RegularText (post-suffix), segments +
         word segments (LIST 278 / wseg after vt+0xb0), quote pairs (LIST 1e8) and parallel structures (LIST 248)
         after post-par)."""
import re, sys, os, subprocess
sys.stdout.reconfigure(encoding='utf-8', errors='backslashreplace')
HERE = os.path.dirname(os.path.abspath(__file__))
EXE = os.path.join(HERE, '..', '..', '..', 'build', 'zf1_t_post.exe')
TOK = re.compile(r'(\w+)=("(?:[^"\\]|\\.)*"|\S+)')


def wline(l):
    d = dict(TOK.findall(l[2:]))
    g = lambda k: d.get(k, '""').strip('"') if d.get(k, '').startswith('"') else d.get(k, '')
    return '\t'.join([d['t'], d['i180'], d['pos'], d['tpos'], d['off'], d['len'], d.get('pron', '0'),
                      d.get('sa', '0000000000000000'), g('text'), g('ne'), g('sas')]), d


def parse(path):
    cases = []   # (label, kind, input_lines, expected_lines)
    lines = open(path, encoding='utf-8', errors='surrogateescape').read().split('\n')
    i = 0; label = ''
    cur = None
    while i < len(lines):
        l = lines[i]
        if l.startswith('L '):
            label = l[:60]
        elif l.startswith('P pre-step9'):
            words = []; i += 1
            while lines[i].startswith('p '): words.append(wline(lines[i])[0]); i += 1
            assert lines[i].startswith('P post-step9'); i += 1
            exp = ['W9']
            while i < len(lines) and lines[i].startswith('p '):
                d = wline(lines[i])[1]; exp.append('w %s %s' % (d['t'], d['i180'])); i += 1
            cases.append((label, 'W9', words, exp)); continue
        elif l.startswith('P pre-vtb0'):
            words = []; i += 1
            while lines[i].startswith('p '): words.append(wline(lines[i])[0]); i += 1
            segs = []; wsegs = []
            while not lines[i].startswith('P pre-detect'):
                if lines[i].startswith('  seg '): segs.append(lines[i].strip())
                if lines[i].startswith('  wseg '): wsegs.append(lines[i].strip())
                i += 1
            while not lines[i].startswith('P post-detect'): i += 1
            typ = re.search(r'type=(\d+)', lines[i]).group(1)
            while not lines[i].startswith('P post-suffix'): i += 1
            i += 1; regs = []
            while lines[i].startswith('p '):
                d = wline(lines[i])[1]; regs.append('r ' + re.sub(r'\\x([0-9a-f]{2})', lambda m: chr(int(m.group(1), 16)), d['reg'].strip('"'))); i += 1
            while not lines[i].startswith('P post-par'): i += 1
            i += 1; quotes = []; pars = []
            while i < len(lines) and (lines[i].startswith('LIST') or lines[i].startswith('  ')):
                s = lines[i].strip()
                if s.startswith('quote'):
                    m = re.match(r'quote (-?\d+)\((\d+)\) (-?\d+)\((\d+)\)', s); quotes.append('quote %s %s' % (m.group(2), m.group(4)))
                if s.startswith('par'): pars.append(s)
                i += 1
            exp = ['SENT type=%s' % typ] + regs + [re.sub(r'^seg (\S+) (\S+) "(.*)"$', r'seg \1 \2 \3', s) for s in segs] + wsegs + quotes + pars
            exp = [re.sub(r'\\x([0-9a-f]{2})', lambda m: chr(int(m.group(1), 16)), e) for e in exp]
            cases.append((label, 'SENT', words, exp)); continue
        i += 1
    return cases


def main():
    cases = []
    for p in sys.argv[1:]: cases += parse(p)
    inp = os.path.join(HERE, 'cases.txt')
    with open(inp, 'w', encoding='utf-8', errors='surrogateescape') as f:
        for label, kind, words, exp in cases:
            f.write(kind + '\n' + ''.join(w + '\n' for w in words) + 'END\n')
    out = subprocess.run([EXE, inp], capture_output=True).stdout.decode('utf-8', 'surrogateescape').replace('\r', '').split('\n')
    # split output into blocks
    blocks = []; cur = None
    for l in out:
        if l in ('W9',) or l.startswith('SENT'):
            cur = [l]; blocks.append(cur)
        elif cur is not None and l:
            cur.append(l)
    bad = {'W9': 0, 'SENT': 0}; tot = {'W9': 0, 'SENT': 0}; shown = 0
    for (label, kind, words, exp), got in zip(cases, blocks):
        tot[kind] += 1
        if exp != got:
            bad[kind] += 1
            if shown < 12:
                shown += 1
                print(kind, label)
                for k in range(max(len(exp), len(got))):
                    e = exp[k] if k < len(exp) else '-'; g = got[k] if k < len(got) else '-'
                    if e != g: print('   E', e, '\n   P', g)
    if len(blocks) != len(cases): print('BLOCK COUNT', len(blocks), len(cases))
    for k in tot: print('%s: %d/%d identical' % (k, tot[k] - bad[k], tot[k]))


if __name__ == '__main__':
    main()
