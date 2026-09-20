"""Reference model of the OneCore SPS vocoder FIXED-POINT path (CExcitationGeneratorImpl<int> +
CLsfSynthesizerImpl<short,int>), used by OneCore Zira and Mark (APM header u32 at file offset 0x24 == 1).
Verifies against harness/vocprobe.exe dumps:  python vocoder_model_int.py vocdump.bin [LsfSharpen.Step]
"""
import sys, struct, math
import numpy as np
import pefile
from vocoder_model import DLL, f32, Excitation, softclip, read_dump


def cdiv(a, b):
    """C integer division (truncation toward zero)."""
    q = abs(a) // abs(b)
    return q if (a >= 0) == (b > 0) else -q


def dll_int_tables():
    pe = pefile.PE(DLL, fast_load=True)
    b = pe.OPTIONAL_HEADER.ImageBase
    img = pe.get_memory_mapped_image()
    cos_tab = struct.unpack_from('<2048h', img, 0x1801866d0 - b)    # ~round(32767*cos(2*pi*i/4096))
    exp_tab = struct.unpack_from('<1331h', img, 0x1801876d0 - b)    # ~trunc(exp(i/128))
    return cos_tab, exp_tab


def f2s(x):
    """(int)(short)(int)x : float->int truncation, then wrap to int16"""
    v = int(x)
    return ((v + 0x8000) & 0xffff) - 0x8000


class IExcitation(Excitation):
    """CExcitationGeneratorImpl<int> (vtbl 0x180177aa8): Q13 taps / Q13 raw noise / Q14 filtered noise -> Q14 excitation."""
    def __init__(self, fs=16000, rnd=None):
        super().__init__(fs, rnd)                                               # same float noise/filters, then quantised
        self.hv_i = [f2s(f32(8192.0) * v) for v in self.hv]                      # FUN_1800472b8(.., 0x2000, 41)
        self.noise_i = [f2s(f32(8192.0) * v) for v in self.noise]               # +0x1048
        self.noise_uv_i = [f2s(f32(16384.0) * v) for v in self.noise_uv]        # +0x1050
        e = f32(0.0)
        for v in self.noise: e = f32(e + f32(v * v))
        a = f32(f32(1024.0) / e)
        i1 = int(f32(f32(a * f32(16384.0)) * f32(16384.0)))                    # FUN_18010b7e0
        self.g40_i = f2s(math.sqrt(float(cdiv(i1, 40))))
        self.g80_i = f2s(math.sqrt(float(cdiv(i1, 80))))

    def pulses_i(self, f0, n, shift):
        """FUN_18004b864: as Excitation.pulses but F0 is int Hz and T = fs / F0 (unsigned integer division)."""
        p = np.zeros(n, np.int32); s = 0
        for i in range(len(f0)):
            if s >= n: break
            f = int(f0[i])
            if float(f) <= 3.0:
                f = 0
            else:
                if float(int(self.prevf0)) <= 3.0:
                    p[s] = 1; self.last = s
                T = self.fs // (f & 0xffffffff)
                if T:
                    m = s
                    while m < s + shift:
                        k = ((m - self.last) & 0xffffffff) // T
                        if k >= 1:
                            step = T; base = self.last
                            for _ in range(k):
                                pos = step + base
                                if pos < 0: p[0] = 1
                                elif pos < n: p[pos] = 1
                                step += T; self.last = m; base = m
                        m += 1
            self.prevf0 = f
            s += shift
        self.last -= n
        return p

    def run_i(self, f0, n, shift):
        p = self.pulses_i(f0, n, shift)
        T = 41; out = [0] * n; h = self.hv_i                              # FUN_180041890 (int overlap-add)
        if self.hist is not None:
            for i in range(T):
                if self.hist[i]:
                    for k in range(T):
                        if i + k >= T and i + k - T < n: out[i + k - T] += h[k]
        for m in range(n):
            if p[m]:
                for k in range(T):
                    if m + k < n: out[m + k] += h[k]
        self.hist = p[n - T:].copy() if n >= T else np.concatenate([self.hist[n:], p])
        g = self.g40_i if shift == 40 else self.g80_i                          # FUN_180060d58
        for i in range(len(f0)):
            if (i + 1) * shift > n: break
            r = self.rnd.rand()
            off = shift + r % (1024 - 2 * shift)
            for k in range(shift):
                j = i * shift + k
                if float(int(f0[i])) <= 3.0:
                    out[j] = cdiv(g * self.noise_i[off + k], 0x2000)
                else:
                    out[j] = cdiv(g * self.noise_uv_i[off + k], 0x4000) + out[j] * 2
        return np.array(out, np.int64)


def ilsp2lpc(c, p):
    """FUN_18003b460: Q15 cosines -> int LPC; int64 Q30 polynomials; LSP pairs consumed in a permuted order."""
    n = p // 2
    P = [1 << 30, c[0] * -65536]; Q = [1 << 30, c[1] * -65536]
    for i in range(1, n):
        if i % 2 == 0: idx = 2 * i
        elif n % 2 == 0: idx = 2 * (n - i)
        else: idx = 2 * (n - i) - 2
        d = c[idx] * -2; e = c[idx + 1] * -2
        P2 = [0] * (i + 2); Q2 = [0] * (i + 2)
        P2[0] = Q2[0] = 1 << 30
        P2[i + 1] = ((d * P[i]) >> 15) + P[i - 1] * 2
        Q2[i + 1] = ((e * Q[i]) >> 15) + Q[i - 1] * 2
        for j in range(i, 1, -1):
            P2[j] = ((d * P[j - 1]) >> 15) + P[j - 2] + P[j]
            Q2[j] = ((e * Q[j - 1]) >> 15) + Q[j - 2] + Q[j]
        P2[1] = ((d * P[0]) >> 15) + P[1]
        Q2[1] = ((e * Q[0]) >> 15) + Q[1]
        P, Q = P2, Q2
    a = [0] * p
    for j in range(1, n + 1):
        s = (Q[j] - Q[j - 1]) + P[j] + P[j - 1]
        t = (P[j] + P[j - 1]) - (Q[j] - Q[j - 1])
        a[j - 1] = cdiv(s, 32768); a[p - j] = cdiv(t, 32768)
    return a


class ISynth:
    """CLsfSynthesizerImpl<short,int>::Synthesize = FUN_18006c250 (no warp / power normalisation)."""
    def __init__(self, order):
        self.hist = [0] * order
        self.cos_tab, self.exp_tab = dll_int_tables()

    def run(self, lsf, gain, exc, shift):
        p = lsf.shape[1]; nfr = lsf.shape[0]
        out = np.zeros(nfr * shift, np.int16)
        B = self.hist + [0] * shift
        for u in range(nfr):
            G = int(gain[u])
            g = self.exp_tab[min(cdiv(G + 0x80, 0x100), 0x532)] if G != 0 else 0
            c = [self.cos_tab[min(cdiv(int(x), 8), 0x7ff)] for x in lsf[u]]
            a = ilsp2lpc(c, p)
            tries = 0
            while True:
                tries += 1; bad = False
                for n in range(shift):
                    acc = int(exc[u * shift + n]) * g * 4
                    for k in range(p):
                        acc += -B[n + p - 1 - k] * a[k]
                    y = max(-0x8000, min(0x7fff, acc >> 16))
                    B[n + p] = y
                    if tries < 5 and (y > 31000 or y < -31000):
                        bad = True; break
                    out[u * shift + n] = softclip(f32(y))
                if not bad: break
                fac = f32(0.99); m = f32(0.99)                                   # FUN_18010bc78
                for k in range(p):
                    a[k] = int(f32(f32(a[k]) * fac)); fac = f32(fac * m)
            B[:p] = B[shift:shift + p]
        self.hist = B[:p]
        return out


def isharpen(row, intervals, iters, step, low, high):
    """FUN_18003af48 / FUN_18003b084 / FUN_18003b2c0 (MultipleInterval, Q15 LSF, C int arithmetic)."""
    x = [int(v) for v in row]; p = len(x)
    st = f2s(f32(step) * f32(32768.0)); lo = f2s(f32(low) * f32(32768.0)); hi = f2s(f32(high) * f32(32768.0))
    d = intervals
    for it in range(iters):
        if d == 0: d = 1
        acc = [0] * p
        for i in range(d, p - d):
            f = x[i]
            if lo < f:
                w = st
                if hi <= f: w = st - cdiv((f - hi) * st, 0x4000 - hi)
            else:
                w = cdiv(f * st, lo)
            fl = f - x[i - d]; fr = x[i + d] - f
            if fl == 0: c = 0
            else:
                den = cdiv(fr * fr, fl) + fl
                c = 0 if den == 0 else cdiv(w * fr, den)
            delta = cdiv((fl - fr) * c, 0x8000)
            acc[i] += delta
            for j in range(1, d):
                acc[i - j] += cdiv((f - x[i - j]) * delta, fl) if fl != 0 else 0
                acc[i + j] += cdiv((x[i + j] - f) * delta, fr) if fr != 0 else 0
        t = [0] * p; t[0] = x[0]; t[p - 1] = x[p - 1]
        for k in range(1, p - 1):
            t[k] = cdiv(acc[k], min(k, p - 1 - k, 2 * d - 1)) + x[k]
        x[1:p - 1] = t[1:p - 1]
        d -= 1
    tab = [int(f32(v) * f32(16384.0)) for v in (0.28, 0.7, 1.2, 1.8)]   # DAT_1801c0320 (runtime init FUN_1800013e0)
    d = intervals - 1
    while d > 0:
        g = tab[d - 1] // p
        for i in range(p - d):
            gap = x[i + d] - x[i]
            if gap < g:
                adj = cdiv(g - gap, 2); x[i + d] += adj; x[i] -= adj
        d -= 1
    return x


def main(path, step=0.22):
    exc = None; syn = None
    for tag, b in read_dump(path):
        if tag == 'RSET':
            print('RSET')
            if exc is not None: exc.reset()
            if syn is not None: syn.hist = [0] * len(syn.hist)
        elif tag == 'ISHP':
            rows, order = struct.unpack_from('<2I', b)
            bef = np.frombuffer(b, np.int32, rows * order, 8).reshape(rows, order)
            aft = np.frombuffer(b, np.int32, rows * order, 8 + rows * order * 4).reshape(rows, order)
            nb = sum(1 for r in range(rows) if isharpen(bef[r], 2, 3, step, 0.075, 0.4) != list(aft[r]))
            print(f'ISHP frames={rows}: {nb} mismatching frames')
        elif tag == 'IEX0':
            rows, cols, n, sh = struct.unpack_from('<4I', b)
            f0 = np.frombuffer(b, np.int32, rows * cols, 16).reshape(rows, cols)[:, 0]
            ref = np.frombuffer(b, np.int32, n, 16 + rows * cols * 4)
            if exc is None: exc = IExcitation(16000)
            got = exc.run_i(f0, n, sh)
            bad = np.nonzero(got != ref)[0]
            print(f'IEX0 frames={rows} n={n}: {len(bad)} mismatches' + (f' first@{bad[0]} got {got[bad[0]]} ref {ref[bad[0]]}' if len(bad) else ''))
        elif tag == 'ISYN':
            rows, order, grows, gcols, n, sh, itf = struct.unpack_from('<7I', b); o = 40
            lsf = np.frombuffer(b, np.int32, rows * order, o).reshape(rows, order); o += rows * order * 4
            g = np.frombuffer(b, np.int32, grows * gcols, o).reshape(grows, gcols)[:, 0]; o += grows * gcols * 4
            e = np.frombuffer(b, np.int32, n, o); o += n * 4
            ref = np.frombuffer(b, np.int16, n, o)
            if syn is None: syn = ISynth(order)
            got = syn.run(lsf, g, e, sh)
            bad = np.nonzero(got != ref)[0]
            print(f'ISYN frames={rows} n={n}: {len(bad)} mismatches' + (f' first@{bad[0]} got {got[bad[0]]} ref {ref[bad[0]]}' if len(bad) else ''))


if __name__ == '__main__':
    main(sys.argv[1] if len(sys.argv) > 1 else r'D:/llm-experiments/misk/zira/harness/vocdump.bin',
         float(sys.argv[2]) if len(sys.argv) > 2 else 0.22)
