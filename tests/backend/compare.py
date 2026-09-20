"""Compare two 16-bit mono WAV files sample by sample.  python compare.py ref.wav test.wav
Exit 0 iff bit-exact. Prints length, #differing samples, first difference, max abs difference."""
import sys, wave, struct
def pcm(path):
    w = wave.open(path, 'rb'); n = w.getnframes(); d = w.readframes(n); w.close()
    return struct.unpack('<%dh' % (len(d) // 2), d)
def compare(a, b):
    x, y = pcm(a), pcm(b); n = min(len(x), len(y))
    diff = [i for i in range(n) if x[i] != y[i]]
    bad = len(diff) + abs(len(x) - len(y))
    return {'ref_len': len(x), 'len': len(y), 'bad': bad, 'first': diff[0] if diff else None,
            'maxabs': max((abs(x[i] - y[i]) for i in diff), default=0)}
if __name__ == '__main__':
    r = compare(sys.argv[1], sys.argv[2]); print(r); sys.exit(0 if r['bad'] == 0 else 1)
