"""Compare a resynthesis with its original: log-spectral distortion, and an A/B file for listening.

usage: python voc_compare.py orig.wav resyn.wav [more.wav ...] [--ab out.wav]
"""
import argparse
import wave

import numpy as np


def read_wav(path):
    with wave.open(path, "rb") as w:
        return np.frombuffer(w.readframes(w.getnframes()), dtype="<i2").astype(np.float64), w.getframerate()


def write_wav(path, x, rate):
    with wave.open(path, "wb") as w:
        w.setnchannels(1)
        w.setsampwidth(2)
        w.setframerate(rate)
        w.writeframes(np.clip(x, -32768, 32767).astype("<i2").tobytes())


def logspec(x, n=512, hop=80):
    win = np.hanning(n + 2)[1:-1]
    T = max(0, (len(x) - n) // hop)
    S = np.zeros((T, n // 2 + 1))
    for t in range(T):
        S[t] = 20 * np.log10(np.abs(np.fft.rfft(x[t * hop:t * hop + n] * win)) + 1e-3)
    return S


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("files", nargs="+")
    ap.add_argument("--ab")
    args = ap.parse_args()
    ref, rate = read_wav(args.files[0])
    Sr = logspec(ref)
    er = np.sqrt(np.mean(np.reshape(ref[:len(ref) // 80 * 80], (-1, 80)) ** 2, axis=1))
    loud = er > np.percentile(er, 40)
    for f in args.files[1:]:
        y, _ = read_wav(f)
        S = logspec(y)
        T = min(len(Sr), len(S))
        m = loud[:T]
        d = np.sqrt(np.mean((Sr[:T][m] - S[:T][m]) ** 2, axis=1))
        print("%-28s  log-spectral distortion %.2f dB (median %.2f)" % (f.split("/")[-1], d.mean(), np.median(d)))
    if args.ab:
        gap = np.zeros(int(0.45 * rate))
        parts = [ref, gap]
        for f in args.files[1:]:
            y, _ = read_wav(f)
            parts += [y, gap]
        write_wav(args.ab, np.concatenate(parts), rate)
        print("A/B: %s (original, then each resynthesis)" % args.ab)


if __name__ == "__main__":
    main()
