"""Decode the XOR-obfuscated UTF-16 string table of an APM file.
Key = 8 u16 at engine VA 0x1801807d8 (12 34 56 78 9a bc de f0 as LE u16s);
zero code units are kept and do not advance the key index (FUN_180039f60)."""
import struct, sys
KEY = (0x3412, 0x7856, 0xbc9a, 0xf0de, 0x5634, 0xdebc, 0x9a78, 0x12f0)
def decode(buf):
    w = struct.unpack('<%dH' % (len(buf) // 2), buf); out = []; j = 0
    for c in w:
        if c == 0: out.append(0); continue
        out.append(c ^ KEY[j]); j = (j + 1) % 8
    return out
def strings(buf):
    """dict byte_offset -> string"""
    u = decode(buf); res = {}; start = 0
    for i, c in enumerate(u):
        if c == 0:
            if i > start: res[start * 2] = ''.join(map(chr, u[start:i]))
            start = i + 1
    return res
if __name__ == '__main__':
    d = open(sys.argv[1], 'rb').read()
    off, size = struct.unpack_from('<II', d, 0x18 + 0x2c)
    for k, v in strings(d[off:off + size]).items(): print(f'{k:#x}\t{v}')
