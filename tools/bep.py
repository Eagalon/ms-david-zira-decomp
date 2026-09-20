"""BEP ('BEPT') backend-parameter container parser (loader FUN_180113dc0 = CParameterManager load).
Header 0x24: 'BEPT', GUID(16) (must equal engine DAT_18018bac0), u32 version(3), u32 checksum,
u64 payload size (= file size - 0x24).  Payload: u32 N; N x {u32 id (<32), i32 offset, i32 size};
then data blob; offsets relative to blob start; sum(sizes) must equal blob length."""
import struct, sys
def parse(path):
    d = open(path, 'rb').read(); assert d[:4] == b'BEPT'
    ver, ck, size = struct.unpack_from('<IIQ', d, 0x14); assert size == len(d) - 0x24
    n = struct.unpack_from('<I', d, 0x24)[0]; p = 0x28
    ent = [struct.unpack_from('<Iii', d, p + 12 * i) for i in range(n)]
    blob = 0x28 + 12 * n; assert sum(e[2] for e in ent) == len(d) - blob
    return ver, {i: d[blob + o: blob + o + s] for i, o, s in ent}
if __name__ == '__main__':
    ver, E = parse(sys.argv[1])
    for i, b in sorted(E.items()):
        ints = struct.unpack('<%di' % (len(b) // 4), b); fl = struct.unpack('<%df' % (len(b) // 4), b)
        print(i, len(b), ints if len(b) <= 12 else ' '.join('%.4g' % x for x in fl))
