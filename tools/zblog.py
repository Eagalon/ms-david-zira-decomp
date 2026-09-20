"""Reader for harness/zbtap.exe logs (see zbtap.c header). python zblog.py log.bin [-v]"""
import struct, sys
import numpy as np
PH = struct.Struct('<HH6i16i')
def records(path):
    d = open(path, 'rb').read(); o = 0
    while o < len(d):
        tag = d[o:o+4].decode(); n = struct.unpack_from('<I', d, o+4)[0]
        yield tag, d[o+8:o+8+n]; o += 8 + n
def mat(b, dt):
    r, c = struct.unpack_from('<2I', b)
    return np.frombuffer(b, dt, r*c, 8).reshape(r, c) if r*c else np.zeros((r, c), dt)
def utterances(path):
    """list of dicts per utterance; 'hdr' in the first one."""
    utts = []; cur = None; hdr = None; pcm = []
    for tag, b in records(path):
        if tag == 'HDR ': hdr = struct.unpack_from('<4i', b) + (b[16:].decode('utf-16le'),)
        elif tag == 'UTT ':
            cur = {'index': struct.unpack_from('<i', b)[0], 'pcm': []}; utts.append(cur)
        elif tag == 'FEAT':
            nf, npn = struct.unpack_from('<2I', b)
            c = np.frombuffer(b, np.int32, nf*npn*2, 8).reshape(nf, npn, 2)
            cur['kind'] = c[:, :, 0].copy(); cur['val'] = c[:, :, 1].copy()
        elif tag == 'PHON':
            n = struct.unpack_from('<I', b)[0]
            cur['phones'] = [PH.unpack_from(b, 4 + i*PH.size) for i in range(n)]
        elif tag == 'INTF': cur['int'] = struct.unpack_from('<2i', b)[1]
        elif tag in ('DUR ', 'VUV ', 'LF0 ', 'LSF ', 'GAIN', 'FIN0', 'FIN1', 'FIN2'):
            isint = cur.get('int', 0) if tag.startswith('FIN') else None
            dt = np.int32 if tag in ('DUR ', 'VUV ') else np.float32
            cur[tag.strip()] = (b, mat(b, dt))
        elif tag == 'PCM ':
            (cur['pcm'] if cur else pcm).append(np.frombuffer(b, np.int16))
        elif tag == 'UEND' and cur is not None: cur['end'] = True
    return hdr, utts
if __name__ == '__main__':
    hdr, U = utterances(sys.argv[1]); print(hdr)
    for u in U:
        print('utt', u['index'], 'phones', len(u.get('phones', [])), 'feat', u['kind'].shape if 'kind' in u else None,
              {k: v[1].shape for k, v in u.items() if isinstance(v, tuple)}, 'pcm', sum(len(x) for x in u['pcm']))
        if '-v' in sys.argv:
            for i, p in enumerate(u['phones']): print('  ', i, p[:8], 'ctl', p[8:])
            print('  DUR', u['DUR'][1].tolist())
