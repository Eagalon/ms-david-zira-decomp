#!/usr/bin/env python3
"""compare.py ENGINE_DUMP PORT_DUMP [-v N] [-f FIELD,...] [-x FIELD,...] [-l LINE]

Compares the zf1 stage-boundary dumps field by field:
  ENGINE_DUMP = harness/zftap1.exe output (CTTSUtterance tree after CTextProcessor, handler 0x40000)
  PORT_DUMP   = src zf1_main.exe output (same format)
A corpus line is identical when it has the same sentences, the same number of words and every compared field of
every word (and sentence) is equal.  -f limits the comparison to the listed fields, -x excludes fields.
Prints per-field mismatch counts, the first N differing lines (-v, default 10) and the total "identical lines" score.
"""
import sys, re, argparse, collections

sys.stdout.reconfigure(encoding='utf-8', errors='replace')
TOK = re.compile(r'(\w+)=("(?:[^"\\]|\\.)*"|\[[^\]]*\]|\S+)')


def parse(path):
    lines = collections.OrderedDict()
    cur = None
    for raw in open(path, encoding='utf-8', errors='replace'):
        raw = raw.rstrip('\n')
        if raw.startswith('L '):
            no, _, text = raw[2:].partition('\t')
            cur = {'text': text, 'sents': [], 'frags': []}
            lines[int(no)] = cur
        elif cur is None:
            continue
        elif raw.startswith('S '):
            d = dict(TOK.findall(raw[2:]))
            cur['sents'].append({'S': d, 'W': []})
        elif raw.startswith('W '):
            d = dict(TOK.findall(raw[2:]))
            if not cur['sents']:
                cur['sents'].append({'S': {}, 'W': []})
            cur['sents'][-1]['W'].append(d)
        elif raw.startswith('F '):
            cur['frags'].append(raw)
    return lines


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('engine'); ap.add_argument('port')
    ap.add_argument('-v', type=int, default=10)
    ap.add_argument('-f', default='')
    ap.add_argument('-x', default='')
    ap.add_argument('-l', type=int, default=0)
    a = ap.parse_args()
    only = set(filter(None, a.f.split(',')))
    excl = set(filter(None, a.x.split(',')))
    E, P = parse(a.engine), parse(a.port)
    fieldbad = collections.Counter()
    same = 0; shown = 0; total = 0
    for no, e in E.items():
        if a.l and no != a.l: continue
        total += 1
        p = P.get(no)
        diffs = []
        if p is None:
            diffs.append('missing in port')
        else:
            if ((not only) or 'F' in only) and 'F' not in excl and p['frags'] and e['frags'] != p['frags']:
                diffs.append('frags differ: E %s P %s' % (e['frags'], p['frags']))
                fieldbad['F'] += 1
            if len(e['sents']) != len(p['sents']):
                diffs.append('sentences %d vs %d' % (len(e['sents']), len(p['sents'])))
                fieldbad['#sent'] += 1
            for si, (es, ps) in enumerate(zip(e['sents'], p['sents'])):
                for k in sorted(set(es['S']) | set(ps['S'])):
                    if k == 'lists' or (only and 'S.' + k not in only) or 'S.' + k in excl: continue
                    if es['S'].get(k) != ps['S'].get(k):
                        diffs.append('S%d.%s %s vs %s' % (si, k, es['S'].get(k), ps['S'].get(k)))
                        fieldbad['S.' + k] += 1
                ew, pw = es['W'], ps['W']
                if len(ew) != len(pw):
                    diffs.append('S%d words %d vs %d: E[%s] P[%s]' % (si, len(ew), len(pw),
                                 ' '.join(w.get('text', '?') for w in ew), ' '.join(w.get('text', '?') for w in pw)))
                    fieldbad['#words'] += 1
                    continue
                for wi, (x, y) in enumerate(zip(ew, pw)):
                    for k in sorted(set(x) | set(y)):
                        if (only and k not in only) or k in excl: continue
                        if x.get(k) != y.get(k):
                            diffs.append('S%d W%d %s: %s %s vs %s' % (si, wi, x.get('text'), k, x.get(k), y.get(k)))
                            fieldbad[k] += 1
        if not diffs:
            same += 1
        elif shown < a.v:
            shown += 1
            print('L %d  %s' % (no, e['text']))
            for d in diffs[:12]: print('    ' + d)
    print('fields with mismatches (count of word/sentence instances):')
    for k, n in fieldbad.most_common(): print('  %-10s %d' % (k, n))
    print('IDENTICAL LINES: %d / %d' % (same, total))


if __name__ == '__main__':
    main()
