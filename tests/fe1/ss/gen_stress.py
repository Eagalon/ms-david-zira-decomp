"""gen_stress.py N SEED OUT - random sentence-boundary stress lines for the zf1 sentence separator test
(escapes: \\n \\t \\uXXXX are decoded by the test drivers)."""
import random, sys
sys.path.insert(0, 'D:/llm-experiments/misk/zira/tools')
from locdat import Dat, sentsep

N, SEED, OUT = int(sys.argv[1]), int(sys.argv[2]), sys.argv[3]
rnd = random.Random(SEED)
L = sentsep(Dat())
words = ('the cat sat on mat and then it ran away quickly because of dog he she we they said was is are '
         'hello world ok yes no maybe apple orange version item page chapter figure number street doctor').split()
caps = [w.capitalize() for w in words] + ['I', 'John', 'Mary', 'London', 'NASA', 'IBM', 'U.S.', 'A.B.', 'E.U.']
lower_starts = ['and', 'but', 'or', 'nor', 'so', 'then', 'e.g.', 'etc.', 'i.e.']
punct = ['.', '.', '.', '!', '?', '?!', '...', '. . .', '\u2026', ';', ':', ',', '!!', '.)', '.")', '."', ".'", '?"',
         '!"', '.\u201d', '.\u2019', ')', ' -', ' --', '\u3002', '\uff0e', '\uff01', '\uff1f', '.]', '.}']
nums = ['3', '3.5', '12', '1,234', '1.', '2.', '10.', '0.5', '42nd', '1st', '3rd', '1990s', '5%', '$5', '$5.00',
        '12:30', '3:45 p.m.', '5 a.m.', '7/4', '555-1234', 'IV', 'XII', 'iii', '100m', '2.0', 'v1.2.3']
emot = [e for e in L[9]] + [':)', ':-(', ';-)', ':D', ':P', '<3', ':-/', 'XD', '8-)', ':o', '>:(']
urls = ['www.example.com', 'http://a.b.c/d.html', 'john.doe@mail.com', 'C:\\dir\\file.txt', 'example.org.',
        'a.b', 'e.g.', 'file.txt', 'U.S.A.', 'J. R. R. Tolkien', 'St. Louis', 'Dr. No', 'P.S.', 'PS.', 'No. 5',
        'Fig. 3', 'Vol. II', 'pp. 10-12']
seps = [' ', ' ', ' ', '  ', '\t', '\\n', '\\n\\n', '\\r\\n', ' \\n ', '\u00a0', '\u3000']
quotes = ['"', "'", '\u201c', '\u201d', '\u2018', '\u2019', '(', ')', '[', ']', '{', '}', '\u00ab', '\u00bb', '\u300c',
          '\u300d']


def tok():
    r = rnd.random()
    if r < 0.30: return rnd.choice(words)
    if r < 0.40: return rnd.choice(caps)
    if r < 0.50: return rnd.choice(L[0])            # abbreviations
    if r < 0.54: return rnd.choice(L[10])           # titles
    if r < 0.57: return rnd.choice(L[1])            # bible books
    if r < 0.60: return rnd.choice(L[3])            # ambiguous
    if r < 0.63: return rnd.choice(L[4])            # capitalized starters
    if r < 0.65: return rnd.choice(L[7])            # numeric prefixes
    if r < 0.67: return rnd.choice(L[6])            # digit words
    if r < 0.72: return rnd.choice(nums)
    if r < 0.75: return rnd.choice(emot)
    if r < 0.79: return rnd.choice(urls)
    if r < 0.83: return rnd.choice(lower_starts)
    if r < 0.87: return rnd.choice(quotes) + rnd.choice(words)
    if r < 0.90: return rnd.choice(words) + rnd.choice(quotes)
    if r < 0.93: return rnd.choice(words) + rnd.choice(punct)
    if r < 0.95: return rnd.choice(['\u00e9t\u00e9', 'na\u00efve', '\u00dcber', 'CAF\u00c9', '\u03a3\u03bf\u03c6\u03af\u03b1', '\u041c\u043e\u0441\u043a\u0432\u0430', '\u6771\u4eac', '\U0001F600'])
    return rnd.choice(words) + rnd.choice(["'s", "s'", "n't", "'ll", '-' + rnd.choice(words), '_x', '#1', '@home'])


def sentence():
    n = rnd.randint(1, 14)
    s = ''
    for i in range(n):
        s += tok()
        if i < n - 1: s += rnd.choice(seps) if rnd.random() < 0.9 else rnd.choice(punct) + rnd.choice(seps)
    return s + (rnd.choice(punct) if rnd.random() < 0.8 else '')


out = []
for i in range(N):
    k = rnd.randint(1, 5)
    line = ''
    for j in range(k):
        line += sentence()
        if j < k - 1: line += rnd.choice(seps)
    if rnd.random() < 0.03:   # long line (> 500 chars)
        while len(line) < 600: line += ' ' + sentence()
    if rnd.random() < 0.05: line = rnd.choice(seps) + line
    line = line.replace('\\', '\\\\').replace('\\\\n', '\\n').replace('\\\\r', '\\r').replace('\\\\t', '\\t')
    out.append(line)
open(OUT, 'w', encoding='utf-8', errors='surrogatepass').write('\n'.join(out) + '\n')
