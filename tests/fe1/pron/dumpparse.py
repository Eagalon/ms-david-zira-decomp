"""dumpparse.py - parse zftap1 dumps (W lines) into dicts; decode string escapes and pron lists."""
import re
TOK = re.compile(r'(\w+)=("(?:[^"\\]|\\.)*"|\[[^\]]*\]|\S+)')
BS = chr(92)


def unesc(s):
    out = []
    i = 0
    while i < len(s):
        if s[i] == BS and i + 1 < len(s) and s[i + 1] == 'x':
            out.append(chr(int(s[i + 2:i + 4], 16)))
            i += 4
        else:
            out.append(s[i])
            i += 1
    return ''.join(out)


def parse_dump(path):
    res = []
    cur = None
    for raw in open(path, encoding='utf-8', errors='surrogatepass'):
        raw = raw.rstrip('\n')
        if raw.startswith('L '):
            no, _, text = raw[2:].partition('\t')
            cur = (int(no), text, [])
            res.append(cur)
        elif raw.startswith('S ') and cur:
            cur[2].append([])
        elif raw.startswith('W ') and cur:
            d = {}
            for k, v in TOK.findall(raw[2:]):
                if v.startswith('"'):
                    v = unesc(v[1:-1])
                d[k] = v
            if not cur[2]:
                cur[2].append([])
            cur[2][-1].append(d)
    return res


def prons_ids(v):
    """'[*abc|def]' -> [(ids, is_current)], None if absent.  Ambiguity: '*' is also phone 42 (UW)."""
    if v is None:
        return None
    body = unesc(v[1:-1])
    if body == '':
        return []
    res = []
    for e in body.split('|'):
        cur = e.startswith('*')
        if cur:
            e = e[1:]
        if e == '(null)':
            e = ''
        res.append(([ord(c) for c in e], cur))
    return res
