#!/usr/bin/env python3
"""vocabtrie.py - CVocabTrie (engine FUN_18003cbe0/18003cce0 parse, FUN_18002c5f0 match) decoder.
Used by the CWhiteSpaceBreaker (word-breaker resource 629aa5c4/9756c4e5: 3 u32 char tables, then 2 tries).
Usage: vocabtrie.py dump [0|1]      list all vocabulary strings of trie 0 / 1
       vocabtrie.py match TEXT      longest match length in each trie"""
import sys, struct
sys.path.insert(0, 'D:/llm-experiments/misk/zira/tools')
from locdat import Dat

class Trie:
    def __init__(s, buf, off):   # off = absolute file offset of the trie blob (alignment is file-relative)
        s.b = buf; s.o = off
        h = lambda k: struct.unpack_from('<H', buf, off + 2 * k)[0]
        u = lambda k: struct.unpack_from('<I', buf, off + 2 * k)[0]
        assert h(0) < 2
        p = off + 0x30; s.T1 = p
        p += 2 * h(6); p += (p & 2); s.T2 = p
        p += 2 * h(7); p += (p & 2); s.T3 = p
        p += 2 * h(8); p += (p & 2); s.T4 = p
        p += 2 * h(9); p += (p & 2); s.NODES = p
        p += 4 * u(0xe); s.T6 = p
        s.T7 = p + 4 * u(0x10)
        s.T8 = s.T7 + 4 * u(0x12)
        s.ROOT = off + u(0x14)

    def u16(s, a): return struct.unpack_from('<H', s.b, a)[0]
    def u32(s, a): return struct.unpack_from('<I', s.b, a)[0]

    def dec(s, T, p):   # threshold varint -> (index, newp)
        v = s.b[p]; acc = 0; i = 0
        t = s.u16(T)
        while t <= v:
            acc += t; i += 1
            v = ((v - t) * 256 + s.b[p + i]) & 0xFFFF
            t = s.u16(T + 2 * i)
        return (acc + v) & 0xFFFF, p + i + 1

    def node(s, p):     # FUN_18002cc60 -> (c, f, val, p)
        idx, p = s.dec(s.T1, p)
        c = s.u16(s.NODES + 4 * idx); f = s.u16(s.NODES + 4 * idx + 2); val = 0
        if f & 4:
            b0 = s.b[p]
            if b0 >= 0xc0: val = ((s.b[p + 1] & 0x7f) | ((b0 & 0x3f) << 7)) << 8 | s.b[p + 2]; p += 3
            elif b0 >= 0x80: val = (b0 & 0x7f) << 8 | s.b[p + 1]; p += 2
            else: val = b0; p += 1
        return c, f, val, p

    def level(s, base):
        """yield (c, f, childptr) for all siblings of the node list at base (transliteration of the match loop)"""
        c, f, val, p = s.node(base)
        p12 = p
        r = None
        k = f & 0x1d0
        if k == 0x10:
            idx, q = s.dec(s.T4, p); r = q + s.u32(s.T8 + 4 * idx); p = q
        elif k == 0x90:
            _, p = s.dec(s.T3, p)
        elif k == 0x110:
            p += 3
        f0 = r; p11 = p
        while True:
            yield c, f, s.child(f, p12, f0)
            if f & 2:
                if not (f & 0x200):
                    return
                f0 = None
            c, f, val, p12 = s.node(p11)
            p11 = p12; p4 = f0
            k = f & 0x1d0
            if k == 0x10:
                idx, q = s.dec(s.T4, p12)
                if f0 is None: f0 = q
                p11 = q; p4 = f0 + s.u32(s.T8 + 4 * idx)
            elif k == 0x50:
                p4 = p12
            elif k == 0x90:
                _, p11 = s.dec(s.T3, p12)
            elif k == 0x110:
                p11 = p12 + 3
            f0 = p4

    def child(s, f, p12, f0):
        k = f & 0x1c0
        if k == 0: return f0
        if k == 0x40: return p12
        if k == 0x80:
            idx, _ = s.dec(s.T3, p12); return s.ROOT + s.u32(s.T7 + 4 * idx)
        if k == 0x100:
            return s.ROOT + ((s.b[p12] << 16) | (s.b[p12 + 1] << 8) | s.b[p12 + 2])
        return None

    def match(s, text):
        base = s.ROOT; e = 0; best = 0; more = True
        while e < len(text) and more:
            for c, f, ch in s.level(base):
                if c == ord(text[e]): break
            else:
                return best
            base = ch; e += 1
            if f & 1: best = e
            more = bool(f & 0x10)
        return best

    def dump(s, base=None, prefix='', out=None, depth=0):
        if out is None: out = []
        if base is None: base = s.ROOT
        for c, f, ch in s.level(base):
            w = prefix + chr(c)
            if f & 1: out.append(w)
            if f & 0x10 and ch is not None and depth < 200: s.dump(ch, w, out, depth + 1)
        return out

def tries():
    d = Dat(); c, sz = d.res('629aa5c4'); b = d.d
    o = c
    for _ in range(3):
        n = struct.unpack_from('<I', b, o)[0]; o += 4 + 4 * n
    n1 = struct.unpack_from('<I', b, o)[0]
    t0 = Trie(b, o + 4)
    n1a = (n1 + 3) & ~3
    o2 = o + 4 + n1a
    t1 = Trie(b, o2 + 4)
    return t0, t1

if __name__ == '__main__':
    sys.stdout.reconfigure(encoding='utf-8', errors='backslashreplace')
    t = tries()
    if sys.argv[1] == 'dump':
        w = t[int(sys.argv[2])].dump(); print(len(w)); print('\n'.join(w))
    else:
        for tt in t: print(tt.match(sys.argv[2]))
