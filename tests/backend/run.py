"""Backend corpus runner.
  python run.py David|Zira|Mark [--regen] [--only N,M,...] [--corpus other.txt]
For each corpus line: harness/zbtap.exe renders the text with the real engine (SAPI + OneCore token) and writes the
golden log + reference WAV to out/<voice>/NNN.{bin,wav}; build/x64/zb_backtest.exe re-renders the logged feature
matrices with the C backend (out/<voice>/NNN_c.wav); compare.py checks the WAVs sample by sample."""
import os, sys, subprocess, re
from compare import compare
HERE = os.path.dirname(os.path.abspath(__file__)); ROOT = os.path.normpath(os.path.join(HERE, '..', '..'))
TAP = os.path.join(ROOT, 'harness', 'zbtap.exe'); BT = os.environ.get('ZB_BACKTEST') or os.path.join(ROOT, 'build', 'x64', 'zb_backtest.exe')
VOICE = r'C:/Windows/Speech_OneCore/Engines/TTS/en-US/M1033%s'
TOKEN = r'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech_OneCore\Voices\Tokens\MSTTS_V110_enUS_%sM'
def items(path=None):
    out = []
    for line in open(path or os.path.join(HERE, 'corpus.txt'), encoding='utf-8'):
        line = line.strip()
        if not line or line.startswith('#'): continue
        rate, vol = 0, 100
        while line.startswith('@'):
            k, _, line = line.partition(' ')
            if k.startswith('@rate='): rate = int(k[6:])
            elif k.startswith('@vol='): vol = int(k[5:])
        out.append((line, rate, vol))
    return out
def main():
    voice = sys.argv[1]; regen = '--regen' in sys.argv
    only = None
    if '--only' in sys.argv: only = {int(x) for x in sys.argv[sys.argv.index('--only') + 1].split(',')}
    corpus = sys.argv[sys.argv.index('--corpus') + 1] if '--corpus' in sys.argv else None
    od = os.path.join(HERE, 'out' if not corpus else 'out_' + os.path.splitext(os.path.basename(corpus))[0], voice)
    os.makedirs(od, exist_ok=True)
    tagc = os.environ.get('ZB_TAG', '')
    ok = 0; n = 0; fails = []
    for i, (text, rate, vol) in enumerate(items(corpus)):
        if only is not None and i not in only: continue
        n += 1; base = os.path.join(od, '%03d' % i)
        if regen or not os.path.exists(base + '.bin'):
            subprocess.run([TAP, text, base + '.wav', base + '.bin', TOKEN % voice, str(rate), str(vol)], check=True,
                           stdout=subprocess.DEVNULL)
        r = subprocess.run([BT, VOICE % voice, base + '.bin', base + '_c%s.wav' % tagc, '-q'], capture_output=True, text=True)
        m = re.search(r'(\d+)/(\d+) utterances bit-exact', r.stdout)
        c = compare(base + '.wav', base + '_c%s.wav' % tagc)
        good = c['bad'] == 0 and m and m.group(1) == m.group(2)
        ok += bool(good)
        if not good:
            fails.append(i)
            print('%03d FAIL wav=%s stages=%s  %s' % (i, c, m.group(0) if m else r.stdout[-200:], text[:60]))
            for l in r.stdout.splitlines():
                if 'MISMATCH' in l or 'differ' in l: print('     ', l.strip())
    print('%s: %d/%d items bit-exact (WAV and all stages)%s' % (voice, ok, n, ('; failing ' + ','.join(map(str, fails))) if fails else ''))
if __name__ == '__main__':
    main()
