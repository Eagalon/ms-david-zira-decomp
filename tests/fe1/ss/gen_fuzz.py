"""gen_fuzz.py N SEED OUT - character-level fuzz lines for the sentence separator (escapes \\n \\t \\r \\uXXXX)."""
import random, sys

N, SEED, OUT = int(sys.argv[1]), int(sys.argv[2]), sys.argv[3]
r = random.Random(SEED)
alpha = list("aAbBeEiIsSxXyYzZ0123456789 .......,,,;;::!!??''\"\"()[]{}<>-_/@#$%&*+=|~`^")
alpha += ['\\n', '\\t', '\\r', '\\\\', ' ', ' ', '  ', ' ', '…', '․', '‥', '“', '”',
          '‘', '’', '«', '»', '。', '．', '！', '？', '「', '」', 'é',
          'É', 'ÿ', 'ß', 'İ', 'Σ', 'σ', 'Ж', '東', '', '', '­',
          '‐', '‑', '—', '°', 'º', '˚', '§', '€', '¿', '¡', '•',
          '−', '\U0001F600', '\\u0085', '\\u000b', '\\u2028', '　', '​', 'Mr.', 'Dr.', 'St.', 'No.',
          'Fig.', 'e.g.', 'P.S.', 'etc.', 'Inc.', 'Jan.', 'U.S.', 'Matt.', ':-)', ':(', ';)', 'www.', '.com',
          'http://', '1.', '2)', 'iv.', 'ok', 'OK', 'The', 'And', 'however', 'In', '8/', ':\\\\', '%)']
out = []
for i in range(N):
    n = r.randint(1, 40)
    out.append(''.join(r.choice(alpha) for _ in range(n)))
open(OUT, 'w', encoding='utf-8').write('\n'.join(out) + '\n')
