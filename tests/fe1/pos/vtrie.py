#!/usr/bin/env python3
"""vtrie.py - CVocabTrie (CRF feature vocabulary) decoder, python model of FUN_18003cce0 / FUN_18002c5f0.
   vtrie.py MODELIDX   -> enumerate all feature strings of polyphony CRF model MODELIDX with their ids."""
import struct, sys
sys.path.insert(0, r'D:/llm-experiments/misk/zira/tools')
from locdat import Dat


class Trie:
    def __init__(s, D, o):
        s.D = D
        h = struct.unpack_from('<12H', D, o)
        nA, nB, nC, nD = h[6], h[7], h[8], h[9]
        nE, nF, nG, root = struct.unpack_from('<4I', D, o + 0x1c)
        p = o + 0x30
        def al(q): return q + 2 if (q & 2) else q
        s.A = struct.unpack_from('<%dH' % nA, D, p); p = al(p + 2 * nA)
        p = al(p + 2 * nB)
        s.C = struct.unpack_from('<%dH' % nC, D, p); p = al(p + 2 * nC)
        s.Dt = struct.unpack_from('<%dH' % nD, D, p); p = al(p + 2 * nD)
        s.E = [struct.unpack_from('<2H', D, p + 4 * i) for i in range(nE)]; p += 4 * nE
        p += 4 * nF
        s.G = struct.unpack_from('<%dI' % nG, D, p); p += 4 * nG
        s.H = p
        s.root = o + root

    def dec(s, tab, p):
        D = s.D; v = D[p]; k = 0; acc = 0
        while tab[k] <= v:
            acc += tab[k]; v = (v - tab[k]) * 256 + D[p + k + 1]; k += 1
        return acc + v, p + k + 1

    def hval(s, i): return struct.unpack_from('<I', s.D, s.H + 4 * i)[0]

    def node(s, p, childbase):
        """read one sibling at p: returns (ch, fl, cnt, p_after_hdr(pbVar12), p_next_sibling, childbase)"""
        D = s.D
        idx, p = s.dec(s.A, p)
        ch, fl = s.E[idx]
        cnt = 0
        if fl & 4:
            b = D[p]
            if b >= 0xc0: cnt = ((D[p + 1] & 0x7f) | ((b & 0x3f) << 7)) << 8 | D[p + 2]; p += 3
            elif b >= 0x80: cnt = (b & 0x7f) << 8 | D[p + 1]; p += 2
            else: cnt = b; p += 1
        q = p
        k = fl & 0x1d0
        if k == 0x10:
            i, q = s.dec(s.Dt, q)
            if childbase is None: childbase = q
            childbase = childbase + s.hval(i)
        elif k == 0x50:
            childbase = q
        elif k == 0x90:
            i, q = s.dec(s.C, q)
        elif k == 0x110:
            q += 3
        return ch, fl, cnt, p, q, childbase

    def child(s, fl, p12, childbase):
        k = fl & 0x1c0
        if k == 0: return childbase
        if k == 0x40: return p12
        if k == 0x80:
            i, _ = s.dec(s.C, p12)
            return s.root + s.G[i]
        if k == 0x100:
            D = s.D
            return s.root + (D[p12] << 16 | D[p12 + 1] << 8 | D[p12 + 2])
        return None

    def enum(s):
        out = []
        def walk(p, prefix, cnt0):
            wid = cnt0
            cb = None
            while True:
                ch, fl, cnt, p12, q, cb2 = s.node(p, cb)
                cb = cb2
                w = prefix + chr(ch)
                if fl & 1:
                    wid += 1
                    out.append((wid, w))
                if fl & 0x10:
                    c = s.child(fl, p12, cb)
                    walk(c, w, wid)
                wid += cnt
                if fl & 2:
                    if fl & 0x200:
                        p = q; continue
                    break
                p = q
        walk(s.root, '', -1)
        return out


if __name__ == '__main__':
    d = Dat(); c, sz = d.res('d49f77b9'); D = d.d
    sp, mb, n = struct.unpack_from('<3I', D, c)
    offs = struct.unpack_from('<%dI' % n, D, c + 12)
    mi = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    o = c + mb + offs[mi]
    hdr = struct.unpack_from('<7I', D, o + 0x24)
    t = Trie(D, o + 0x44 + 4 * (hdr[2] + hdr[3]))
    sys.stdout.reconfigure(encoding='utf-8')
    for wid, w in t.enum():
        print(wid, w)


def lookup(t, key):
    """transliteration of FUN_18002c5f0 (returns id, matched length)"""
    L = len(key)
    it13 = -1; it14 = -1; d8 = 0; pos = 0
    cur = t.root; flags = 0x10
    while pos != L and (flags & 0x10):
        ch, fl, cnt, p12, q, cb = t.node(cur, None)
        if fl & 1: it13 += 1
        flags = fl
        while ch != ord(key[pos]):
            i1 = cnt + it13
            if flags & 2:
                if not (fl & 0x200):
                    return it14, d8
                cb = None
            ch, fl, cnt, p12, q, cb = t.node(q, cb)
            it13 = i1 + (1 if fl & 1 else 0)
            flags = fl
        cur = t.child(fl, p12, cb)
        pos += 1
        if fl & 1:
            d8 = pos; it14 = it13
    return it14, d8
