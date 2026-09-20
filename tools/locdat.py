#!/usr/bin/env python3
"""locdat.py - parser for the OneCore TTS language data container (MSTTSLocEnUS.dat, enUS.*.dat).

Usage:
  locdat.py [--file F] toc                  table of contents (type/id GUIDs, offsets, names)
  locdat.py [--file F] lex WORD...          look up words in the compressed lexicon (7bd71f46)
  locdat.py [--file F] lexdump [N]          dump first N lexicon entries in hash-slot order
  locdat.py phones                          phone set (29a5584b)
  locdat.py sentsep                         sentence-separator word lists (e67ab014)
  locdat.py chartable [N]                   character reading table (f6e4f50a)
  locdat.py lts                             CART letter-to-sound model summary (ac4aefcf)
  locdat.py poly                            polyphony CRF model list (d49f77b9)
  locdat.py misc                            small tables (quotes, suffixes, pos-tagger rules, fst headers)

Container: every chunk = {GUID type; GUID id; u64 size; u8 data[size]} padded to 8 bytes.
Root chunk 099f9814 contains 3e13f66a (header: 33c56624 = {u32 ver=1, u32 0, u32 LCID, u32 0})
and e5f704bc (the resource list).  The engine maps the file (FUN_180134f80 -> FUN_18005d5f8
MapViewOfFileEx) and indexes the resource list (FUN_1801350c0); resources are fetched with
IResourceMgr::vt+0x00/+0x08 (type GUID, id GUID, &ptr, &size[, &file]); 0x8004801A = not present.
"""
import struct, sys, uuid

DEFAULT = r'C:\Windows\Speech_OneCore\Engines\TTS\en-US\MSTTSLocEnUS.dat'

NAMES = {
    '099f9814': 'ROOT container',
    '3e13f66a': 'HEADER container',
    '33c56624': 'header {ver,0,LCID,0}',
    'e5f704bc': 'RESOURCE container',
    '00a2359e': 'sPMM pattern-machine data (CRuleSentAndPuncDetector / CShareablePatternMachineData)',
    '0cb71848': 'POS tagger rules (CPosTagger, Brill-style lexical+contextual rules)',
    '19a6569a': 'COMPOUNDPRON transducer network (CWordPronouncer compound pron)',
    '29a5584b': 'phone set (id,name,flags) 46 x 52 bytes',
    '388b0327': 'phone-converter transducer network (mixlingual es-MX -> native)',
    '5554ba64': 'suffix lists (noun/adj suffixes) for sentence/punc & parallel-structure detection',
    '629aa5c4': 'word breaker data (CWordBreakerInfo, key WORDBREAKER_<lang>)',
    '6f4ac239': 'foreign-language LTS set (LTS_<lang>_<i>; es-MX CART + phone list)',
    '78f6770d': 'syllabification rules (CSyllableSeg)',
    '7bd71f46': 'main lexicon (CTTSLexicon, Huffman-compressed hash lexicon, key LEX@path)',
    '7d5841ab': 'text-normalization transducer network (CTextNormalizer / CNEDetector, key TRANSDUCER_<lang>)',
    '9abda282': 'NUS domain table (26-byte records, FUN_180077090)',
    '9d9e8526': 'phone class groups (7 records) - no reference found in engine/loc DLLs',
    'ac4aefcf': 'letter-to-sound CART (CLTSLexiconCART, key LTS_<lang>)',
    'b54490e3': 'quote-pair table (sentence & punctuation detector)',
    'bfc4309d': 'NE FST (CFstMatcher, key LangDataFstNE, Bing NL platform FST)',
    'd49f77b9': 'polyphony (homograph) CRF models (CCRFPolyphonyTaggerList, 13 words)',
    'd8951565': 'parallel-structure detector config (CParallelStructDetector)',
    'e67ab014': 'sentence separator word lists (SENTSEP_<lang>, FUN_180047748)',
    'e849e61b': 'CPolyphony rule/context-pron data',
    'efdc81f5': 'language identifier model (FUN_1800e0a70) [guess: char n-gram LID for mixlingual]',
    'f6e4f50a': 'char table (symbol readings), 363 x 16-byte records',
    'f81fd1d1': 'POS id list (22 u16) loaded into lexicon object (FUN_1800c19dc)',
    '46ee52ba': 'RNN LTS (CRNNDecoder, key RNNLTS_<lang>) [domain Name.dat only]',
    'cea1be6f': 'acronym CRF tagger list (CCRFAcronymTaggerList) [Address.dat]',
}


class Dat:
    def __init__(s, path=DEFAULT):
        s.d = open(path, 'rb').read()
        s.chunks = []   # (depth, hdr_off, data_off, size, type, id)
        s._walk(0, len(s.d), 0)

    def _walk(s, o, end, dep):
        d = s.d
        while o + 0x28 <= end:
            t = str(uuid.UUID(bytes_le=d[o:o + 16])); i = str(uuid.UUID(bytes_le=d[o + 16:o + 32]))
            sz = struct.unpack_from('<Q', d, o + 32)[0]; c = o + 0x28
            if c + sz > end: raise ValueError('bad chunk at %x' % o)
            s.chunks.append((dep, o, c, sz, t, i))
            if t[:8] in ('099f9814', '3e13f66a', 'e5f704bc'): s._walk(c, c + sz, dep + 1)
            o = (c + sz + 7) & ~7

    def res(s, t8):
        for dep, o, c, sz, t, i in s.chunks:
            if t.startswith(t8): return c, sz
        return None

    def toc(s):
        for dep, o, c, sz, t, i in s.chunks:
            print('%s%08x data@%08x size %8x  %s  id %s  %s' % ('  ' * dep, o, c, sz, t, i, NAMES.get(t[:8], '?')))

    # --- helpers
    def u32(s, o): return struct.unpack_from('<I', s.d, o)[0]

    def wstr(s, o):
        e = o
        while s.d[e:e + 2] != b'\0\0': e += 2
        return s.d[o:e].decode('utf-16le')


# ---------------------------------------------------------------- lexicon (7bd71f46)
class Huff:
    """CLwHuffCodec table: u32 nSym, u32 nNodes(=2n-1), u32 root; u16 sym[nSym]; u32 node[nNodes]
    (node = u16 child0, u16 child1; child0==0xFFFF -> leaf, symbol = sym[node]).  Bits are read
    LSB-first from a u32 word stream."""
    def __init__(s, d, off, words):
        n, nn, root = struct.unpack_from('<3I', d, off)
        s.n, s.root = n, root
        s.sym = struct.unpack_from('<%dH' % n, d, off + 12)
        s.tree = [struct.unpack_from('<2H', d, off + 12 + 2 * n + 4 * k) for k in range(nn)]
        s.w = words

    def one(s, p):
        node = s.root
        while True:
            a, b = s.tree[node]
            if a == 0xFFFF: return s.sym[node], p
            bit = (s.w[p >> 5] >> (p & 31)) & 1; p += 1
            node = b if bit else a

    def string(s, p):
        out = []
        while True:
            c, p = s.one(p)
            if c == 0: return out, p
            out.append(c)


class Lexicon:
    """header (offsets relative to resource start):
      +00 GUID b3884aee-29dc-4038-8c6c-6aab8ba3724c (format)   +20 LCID   +24 total size
      +28 nEntries  +2c/+30/+34/+38 counts (unused here)
      +3c hash table offset, +40 nSlots, +44 bits/slot (MSB-first packed; all-ones = empty)
      +48/+4c codec0 word chars  +50/+54 codec1 phone ids  +58/+5c codec2 pron 'pos' value
      +60/+64 codec3 attribute-set ids  +68/+6c codec4 attribute names
      +70/+74 u32 attrset start[]  +78/+7c attr defs 10-byte recs  +80/+84 u16 attr id lists
      +88/+8c bitstream for attr names  +90/+94 main entry bitstream (u32 words)  +98 nameBits"""
    def __init__(s, dat, base=None):
        s.dat = dat; d = dat.d
        s.L = base if base is not None else dat.res('7bd71f46')[0]
        H = s.H = lambda o: struct.unpack_from('<I', d, s.L + o)[0]
        s.words = struct.unpack_from('<%dI' % (H(0x94) // 4), d, s.L + H(0x90))
        s.C = [Huff(d, s.L + H(k), s.words) for k in (0x48, 0x50, 0x58, 0x60)]
        w5 = struct.unpack_from('<%dI' % (H(0x8c) // 4), d, s.L + H(0x88))
        c5 = Huff(d, s.L + H(0x68), w5)
        p = 0; s.attrnames = []
        while p < H(0x98):
            t, p = c5.string(p); s.attrnames.append(''.join(map(chr, t)))
        starts = struct.unpack_from('<%dI' % (H(0x74) // 4), d, s.L + H(0x70))
        ids = struct.unpack_from('<%dH' % (H(0x84) // 2), d, s.L + H(0x80))
        s.attrsets = []
        for st in starts:
            l = []; j = st
            while ids[j]: l.append(s.attrnames[ids[j]]); j += 1
            s.attrsets.append(l)
        s.hb = s.L + H(0x3c); s.ns = H(0x40); s.bits = H(0x44)

    def slot(s, i):
        d = s.dat.d; v = 0; p = s.bits * i
        for _ in range(s.bits):
            v = (v << 1) | ((d[s.hb + (p >> 3)] >> (7 - (p & 7))) & 1); p += 1
        return v

    def hash(s, w):   # FUN_180035180
        h = prev = ord(w[0])
        for ch in w[1:]:
            c = ord(ch); h = (h + (c << (prev & 31)) + (prev << (c & 31))) & 0xFFFFFFFF; prev = c
        return ((h * 0xFFFF) & 0xFFFFFFFF) % s.ns

    def getbits(s, p, n):
        return sum(((s.words[(p + k) >> 5] >> ((p + k) & 31)) & 1) << k for k in range(n))

    def find(s, w):
        w = w.lower(); i = s.hash(w)
        for _ in range(s.ns):
            v = s.slot(i)
            if v == (1 << s.bits) - 1: return None
            cs, p = s.C[0].string(v)
            if ''.join(map(chr, cs)) == w: return p
            i = (i + 1) % s.ns
        return None

    def entry(s, p):   # FUN_180044304
        out = []
        while True:
            h = s.getbits(p, 4); p += 4; t = h & 7
            if t == 1:
                ph, p = s.C[1].string(p); out.append({'phones': ph})
            elif t == 2:
                v, p = s.C[2].one(p); out[-1]['val'] = v
            elif t == 3:
                v, p = s.C[3].string(p); out[-1]['attrs'] = [s.attrsets[k - 1] for k in v]
            else:
                raise ValueError('bad record type %d' % t)
            if h & 8: return out


def phoneset(dat):
    c, sz = dat.res('29a5584b')
    rs, n = struct.unpack_from('<2I', dat.d, c)
    out = {}
    for k in range(n):
        o = c + 8 + rs * k
        pid = struct.unpack_from('<H', dat.d, o)[0]
        nm = dat.d[o + 2:o + 48].decode('utf-16le').split('\0')[0]
        fl = struct.unpack_from('<I', dat.d, o + 48)[0]
        out[pid] = (nm, fl)
    return out


def sentsep(dat):
    c, sz = dat.res('e67ab014'); d = dat.d
    n = dat.u32(c); cnt = struct.unpack_from('<%dI' % n, d, c + 4)
    tot = sum(cnt); offs = struct.unpack_from('<%dI' % tot, d, c + 4 + 4 * n); pool = c + 4 + 4 * n + 4 * tot
    lists = []; k = 0
    for m in cnt:
        lists.append([dat.wstr(pool + offs[k + j]) for j in range(m)]); k += m
    return lists


def chartable(dat):
    c, sz = dat.res('f6e4f50a'); n = dat.u32(c); pool = c + 4 + 16 * n
    return [(ch, fl, dat.wstr(pool + a), dat.wstr(pool + b))
            for ch, fl, a, b in (struct.unpack_from('<4I', dat.d, c + 4 + 16 * i) for i in range(n))]


def lts(dat, base=None, size=None):
    if base is None: base, size = dat.res('ac4aefcf')
    d = dat.d; p = [base]
    def u():
        v = struct.unpack_from('<I', d, p[0])[0]; p[0] += 4; return v
    def symtab():
        st = p[0]; sz = u(); n = u(); offs = struct.unpack_from('<%dI' % n, d, p[0]); p[0] += 4 * n
        sl = u(); pool = d[p[0]:p[0] + sl]; p[0] = st + sz
        r = []
        for o in offs:
            e = o * 2
            while pool[e:e + 2] != b'\0\0': e += 2
            r.append(pool[o * 2:e].decode('utf-16le'))
        return r
    letters = symtab(); outs = symtab()
    n1, m1 = u(), u(); p[0] += 4 * n1 * m1
    n2, m2 = u(), u(); p[0] += 4 * n2 * m2
    st = p[0]; szc = u(); cc = u(); p[0] = st + szc
    trees = []
    for L in letters[1:]:
        st = p[0]; sz = u(); nn = u(); p[0] += 4 * nn; nl = u(); p[0] += nl; nq = u(); p[0] += nq
        trees.append((L, nn, nl, nq)); p[0] = st + sz
    return dict(letters=letters, outputs=outs, mat1=(n1, m1), mat2=(n2, m2), secC=cc, trees=trees,
                end_ok=(p[0] == base + size))


def poly(dat):
    c, sz = dat.res('d49f77b9'); d = dat.d
    sp, mb, n = struct.unpack_from('<3I', d, c)
    offs = struct.unpack_from('<%dI' % n, d, c + 12); noff = struct.unpack_from('<%dI' % n, d, c + 12 + 4 * n)
    return [(dat.wstr(c + sp + noff[i]), c + mb + offs[i]) for i in range(n)]


def main():
    a = sys.argv[1:]; path = DEFAULT
    if a[:1] == ['--file']: path = a[1]; a = a[2:]
    dat = Dat(path); cmd = a[0] if a else 'toc'
    if cmd == 'toc': dat.toc()
    elif cmd in ('lex', 'lexdump'):
        lx = Lexicon(dat)
        try: ph = phoneset(Dat(DEFAULT))
        except Exception: ph = {}
        def fmt(e):
            return ' '.join(ph.get(x, (str(x),))[0].lower() for x in e['phones'])
        words = a[1:] if cmd == 'lex' else None
        if cmd == 'lexdump':
            n = int(a[1]) if len(a) > 1 else 20; words = []
            for i in range(lx.ns):
                v = lx.slot(i)
                if v != (1 << lx.bits) - 1:
                    cs, p = lx.C[0].string(v); words.append(''.join(map(chr, cs)))
                    if len(words) >= n: break
        for w in words:
            p = lx.find(w)
            if p is None: print('%-14s NOT FOUND' % w); continue
            for e in lx.entry(p):
                print('%-14s /%s/  val=%s  %s' % (w, fmt(e), hex(e.get('val', 0)), e.get('attrs')))
    elif cmd == 'phones':
        for k, (nm, fl) in sorted(phoneset(dat).items()): print('%3d %-6s %08x' % (k, nm, fl))
    elif cmd == 'sentsep':
        for i, l in enumerate(sentsep(dat)): print(i, len(l), l[:15])
    elif cmd == 'chartable':
        t = chartable(dat); n = int(a[1]) if len(a) > 1 else 40
        for ch, fl, x, y in t[:n]: print('U+%04X %08x %r %r' % (ch, fl, x, y))
        print(len(t), 'records')
    elif cmd == 'lts':
        r = lts(dat)
        print('letters', r['letters']); print(len(r['outputs']), 'output symbols', r['outputs'][:40], '...')
        print('mat1', r['mat1'], 'mat2', r['mat2'], 'secC u16 count', r['secC'], 'parsed to end:', r['end_ok'])
        for t in r['trees']: print('  tree %-2s nodes %6d leafbytes %6d qbytes %7d' % t)
    elif cmd == 'poly':
        for w, o in poly(dat):
            print('%-10s model @%x  %s' % (w, o, dat.d[o + 36:o + 40]))
    elif cmd == 'misc':
        d = dat.d
        c, _ = dat.res('b54490e3'); lc, n = struct.unpack_from('<2I', d, c)
        print('quote pairs', [tuple(hex(x) for x in struct.unpack_from('<HHI', d, c + 8 + 8 * i)) for i in range(n)])
        c, _ = dat.res('5554ba64'); lc, rs, n = struct.unpack_from('<3I', d, c)
        print('noun suffixes', [d[c + 12 + rs * i:c + 12 + rs * (i + 1)].decode('utf-16le').rstrip('\0') for i in range(n)])
        o = c + 12 + rs * n; n2 = dat.u32(o)
        print('adj suffixes ', [d[o + 4 + rs * i:o + 4 + rs * (i + 1)].decode('utf-16le').rstrip('\0') for i in range(n2)])
        c, sz = dat.res('0cb71848'); o = c; tabs = [[]]
        while o + 12 <= c + sz and len(tabs) < 3:
            r = d[o:o + 12]; o += 12
            if r == b'\0' * 12: tabs.append([])
            else: tabs[-1].append(struct.unpack('<BBHII', r))
        print('POS tagger: %d lexical rules, %d contextual rules; string pool @+%x' % (len(tabs[0]), len(tabs[1]), o - c))
        for t8 in ('19a6569a', '388b0327', '7d5841ab'):
            c, sz = dat.res(t8)
            print('FST %s magic %s hdr %s' % (t8, uuid.UUID(bytes_le=d[c:c + 16]), struct.unpack_from('<IIHH8I', d, c + 16)))


if __name__ == '__main__':
    main()
