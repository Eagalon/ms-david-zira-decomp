# zf1 fork E: punctuation marking and the post-Analyze sentence steps

Port: `src\zf1_post.h`, `src\zf1_post.c`. Test driver: `src\zf1_t_post.c`. Harness: `harness\zftap1_post.c`, built with `build_zftap1_post.bat`. Tests: `tests\fe1\post\` (`post_cases.py`, `extra*.txt`).
Addresses are for MSTTSEngine_OneCore.dll 10.3.21207.0. Everything below was verified against the running engine unless it says otherwise.

## Result

| suite | step 9 (W9) | post steps (SENT) |
|---|---|---|
| corpus.txt + extra.txt + extra2.txt (questions, lists, quotes, brackets) | **527/527** identical | **526/526** identical |

The SENT column checks sentence type, RegularText of every word, segments and word→segment links, quote pairs, and parallel structures.

Run the tests with:

```
harness\zftap1_post.exe david tests\fe1\corpus.txt tests\fe1\post\corpus_post.dump   (likewise extra, extra2)
src\cl64.bat /nologo /O2 /W3 /Fo..\build\post\ /Fe:..\build\zf1_t_post.exe zf1_t_post.c zf1_post.c zf1_dat.c zf1_util.c
python tests\fe1\post\post_cases.py tests\fe1\post\corpus_post.dump tests\fe1\post\extra_post.dump tests\fe1\post\extra2_post.dump
```

## Harness (zftap1_post)

The harness hooks call sites. It rewrites the rel32 of a `call` to go to a stub page allocated within ±2 GB of the DLL, so the original functions stay untouched.

| hook | point | what it logs |
|---|---|---|
| 0x5cadc | call 1800b7358 | "pre-detect" words, "post-detect" type |
| 0x5cbfc | call 18001bf24 | "post-suffix" words |
| 0x5cc0e | call 1800b8608 | quote step (the lists are printed after the parallel step) |
| 0x5cc20 | call 1800b90a8 | "post-par" + all lists |
| 0x65ae3 | call 1800bb3e0 | analyzer list A+0x420, "pre-step9" / "post-step9" |
| CTTSSentence vftable slot 0xb0 | vt+0xb0 | "pre-vtb0" words; afterwards the segment list |
| CTTSSentence vftable slot 0xa0 | vt+0xa0 | "pre-vta0" words |

The harness also prints `POSTAB`: the engine POS object (sentence+0x2d8) vt+8 name and vt+0x10 class for ids 0..79.

**Order inside 18005c794 (observed at runtime):**
1. Analyze (commit).
2. **sentence vt+0xa0 (first call).** FUN_18001a644 builds the syllables and phones and inserts the sentence-initial and TN silence words.
3. vt+0xb0.
4. detector.
5. suffix.
6. quotes.
7. parallel.
8. vt+0xa0 again. This is a no-op because the "built" flag is set.

So the post steps see the word list *with* the silence tokens and with syllables. In the port, "has syllables" is equivalent to "type != 1 and pron non-empty". I checked this on every word of every test.

## POS table object (sentence+0x2d8 = CTTSEngine vt+0x50)

- vt+8(id) returns the name. The names are the lexicon attribute names.
- vt+0x10(id) returns the class.
- vt+0x38 returns the default POS, 50.

Ids 0..49 (name / class):
```
0 unknown/0  1 NOM 2 NOM_CLASS 3 noun (1)  4 VER 5 VER_TYPE 6 verb 7 verbing 8 verbpastp (2)  9 ADJ 10 ADJ_TYPE 11 adj (3)
12 DET 13 DET_TYPE 14 det 15 whdet (4)  16 NUM 17 NUM_TYPE 18 num (5)  19 AUX 20 AUX_TYPE 21 vaux (6)
22 PRO 23 PRO_TYPE 24 pron 25 whpron (7)  26 ADV 27 ADV_TYPE 28 adv 29 whadv (9)  30 CON 31 CON_TYPE 32 conj (10)
33 ADP 34 ADP_TYPE 35 prep (11)  36 INT 37 INT_TYPE 38 interjection (12)  39 PAR 40 PAR_TYPE 41 particle (13)
42 SYM 43 SYM_TYPE 44 symbol (16)  45 OTH 46 OTH_TYPE 47 listitem 48 possend 49 contr (17)
```
Ids ≥ 50 map to "unknown" with class 0. Id 50 is the POS of spelled letters.

## sPMM pattern machine (00a2359e/4d4d5073, 0xeb6 B), `tools\spmm.py` dumps it

This is `CShareablePatternMachineData`. The runner is FUN_18001f36c / 18001f970 / 18001fa3c / 18001ffa8.

**Header (i32):**
- +4 nFeatures = 20
- +8 nEntries = 13
- +0xc offset of the feature-type table (0 = int, 1 = string)
- +0x10 offset of the entry table

**Entries (16 B):**
- Layout: `{a, keyOff, nRules, rulesOff}`. The key is `{u16 len, chars}`.
- The entries are sorted, and the lookup is a binary search on the current word's text: compare the common prefix as u16, then the length.
- Keys: `! ( ) , - -- . ... : ; ? – …`

**Rules (16 B):**
- Layout: `{kind, value, nConds, condsOff}`.
- The first rule whose conditions all hold wins.
- kind 0 means an int result. kind 1 (a string result) does not occur.

**Conditions (16 B):**
- Layout: `{feature, op, unused, operand}`. For string ops the operand is a pool offset of `{u16 len, chars}`.
- Features are evaluated lazily, once per run.

**Operators (table 0x18016d530):**

| op | meaning |
|---|---|
| 1..5 | `== < <= > >=` on ints |
| 6 | eq |
| 7 | startswith |
| 8 | endswith |
| 9 | contains (KMP) |
| 10 | value-in-operand |
| 11 | ieq |
| 12 | istartswith |
| 13 | icontains |
| 14 | i-in |
| 15 | ne |
| 16 | !startswith |
| 17 | !endswith |
| 18 | !ieq |
| 19 | !istartswith |

String length rules and case handling for the operators:
- A string value's length is wcslen capped at 0x800. NULL counts as -1.
- The "i" variants use CRT towlower in the C locale, which folds ASCII only.
- The KMP failure table is always built case-sensitively. That is also true for icontains; the port copies it.

**Features (CRuleSentAndPuncDetector vt+8 = FUN_1800b7560; C = current word):**

| # | value |
|---|---|
| F0 | text of C |
| F1 | POS name of C |
| F2 / F3 | first word of the sentence (FUN_1800b790c: earliest type-0 word walking back over "real" words): text / POS |
| F4 / F5 | second word (FUN_1800b7a80): text / POS |
| F6 / F7 | first word of the last clause (FUN_1800b7990: walk back from C and stop at a punctuation token with i180 in 1..3; segments are jumped as a whole) |
| F8 / F9 | second word of the last clause |
| F10 | number of type-0/4 words in the last clause |
| F11 | `" " + text + " "` for each type-0 word of the last clause (the leading blank comes from CTTSString vt+8(" ")) |
| F12 / F13 | text of the previous / next token |
| F14 / F15 | 1 if there is a gap between prev and C / C and next (FUN_1800b7fd8: same NE entity that is not sp:default, or next.off > off+len) |
| F16 / F17 | POS name of prev / next |
| F18 | `text/POS ` list of the last clause |
| F19 | mode: "S" (sentence detector, 0x180184218) or "W" (word step, 0x180185250) |

A "real" word (FUN_18001a070 == 0) is one that is not silence, not punctuation, and has syllables and a pronunciation.

## Analyze step 9 = FUN_1800bb3e0 → FUN_180060c48 → FUN_1800200dc ("W" mode): `zf1_post_words`

This step runs for every word of the analyzer list, after TN (step 7) and before the pronouncer (step 10). For each word:
- If the text is not a key, nothing is written.
- If a rule gives v ≠ 8: `i180 = v` and `type = 1` (punctuation). The previous token (plain previous, no filtering) also gets `i180 = v`, but only if it is type 0.
- Otherwise `i180 = 8`.

This step is where punctuation gets type 1 and where the boundary classes come from. The W results are:

| token | condition | result |
|---|---|---|
| `,` | followed by a gap, end, `"` or `'` | 1 |
| `-` `–` | spaced dash | 2 |
| `--` `:` | | 2 |
| `;` | | 3 |
| `.` `...` `…` | at the end | 4 |
| `…` | otherwise | 3 |
| `!` | | 5 |
| `?` | | 6 |
| `(` `)` | | 7 |

Tokens that match no rule, such as `"`, `'`, `<`, `&`, stay type 0 with i180 8.

The engine first tries the domain handler's pattern machine (word s1b0 → engine+0x580 map → vt+0x48). The en-US corpus lines with address/name/date domains all matched using the default machine. **Not implemented:** the domain machines from enUS.Address/Name/Message/Media.dat, which also contain 00a2359e.

## After Analyze: `zf1_post_sentence`

**1. vt+0xb0 = FUN_1800b5aa0: segments (sentence+0x278, word+0x1a8).**
- Start at the first word. If it fails FUN_18001a56c or FUN_18001a144, start at the next non-silence word instead.
- A word with a NamedEntityType opens a segment `{w, w, NE}` that runs while src_off (+0x270) stays equal.
- Otherwise, a word whose fragment has a say-as with InterpretAs opens a segment `{w, w, InterpretAs}` that runs while the fragment say-as struct pointer stays the same.
- Otherwise, move to the next non-silence word.
- Port output: `zf1_postout.segs` / `word_seg`, plus `zf_word.ne_obj` (1 on the first word, 2 on the rest).

**2. FUN_1800b7358 (CSentAndPuncDetector).**
- The CRF detector is absent, and the default domain has no handler.
- The "S" pattern machine runs on the **last** token of the sentence (+0x110 tail).
- If a rule matches, the value becomes the sentence type (+0xa8). Otherwise the type is 0.

| type | meaning | example |
|---|---|---|
| 0 | statement | |
| 1 | yes/no question | |
| 2 | wh-question: first word or clause word istartswith "wh", or how/how's/how're/how'd, or prep/conj/adv followed by such a word | |
| 3 | exclamation `!` or `...` + more | |
| 6 | one-word question | "OK?" |
| 7 | alternative question | the last clause contains " or " |

**3. FUN_18001bf24: RegularText (+0xb8).** Start from `towlower(Text)` (ASCII only). Then:
- If `'` occurs, keep the text from its last occurrence onward (`'s`, `'t`, `'ll`, `'`).
- Otherwise, by POS class, if the word ends with a suffix of the class table, RegularText becomes `"-" + suffix`:

| class | table |
|---|---|
| 1 noun | ance ancy crat ence ency hood lity logy ment ness rian ship tion age ant dom eer ent ese ess ine ing ism ist let ure ee |
| 3 adj | able less like some stic cal ese est ful ile ing ish ive ous ed |
| 2 verb | ing ify ise ize yse yze ed en |

The resource is 5554ba64: `u32 LCID, u32 20, 4 × {u32 n, wchar[10] n}` in the order noun, adj, verb, apostrophe. The noun/adj/verb test is "the last occurrence is at the end".

**4. FUN_1800b8608: quote pairs → `zf_sentence.quotes` (+0x1e8).**
- Resource b54490e3: pairs `" "`, `' '`, U+2018/2019, U+201C/201D, with a typographic flag.
- One-character tokens of type 0/1 that are in the table are candidates.
- If a stack item with the same table entry exists, pair with the topmost one and pop everything above it. Otherwise push.
- Smart quotes are already turned into ASCII when the word is created (180062900), so the pairing effectively toggles.

**5. FUN_1800b90a8: parallel structures → `zf_sentence.par` (+0x248).**
- Config d8951565: `u32 LCID, u32 0x2c`, then separators `{44 ","}` and conjunctions `{32 and, 32 or, 32 nor}`.
- A match needs `tpos` (+0x13a) equal and a `_wcsicmp` text match.
- Walk the words up to the last one. At each conjunction w, walk back from the previous content word (FUN_1800b6688):
  - FUN_1800b8d80 collects conjuncts. It stops at a separator, a punctuation token, or the end word of the previous structure.
  - It counts type-0 words. States: 0 → 2 (≤2 words ending at a comma), 2 → 2/1, a final stretch that is not a comma → 1.
  - The conjuncts are pushed to the front.
- If there are more than one, every conjunct's end word must have the same POS class (from tpos) as the last conjunct's (FUN_1800b8bb0).
- Then scan forward from w+1 to the next separator or punctuation, jumping over segments. The last word that satisfies FUN_18001a144 becomes the end of the conjunct `{w, end, 3}`. The structure is kept and the scan continues after `end`.
- Element type: 1 = opener, 2 = middle, 3 = the conjunction's conjunct.

## Known gaps

- The domain pattern machines are not loaded (see step 9).
- The "message" domain branch in 18005c794 is not ported. It applies only when a word's domain is "message", and the default is "general".
- The CRF sentence-type detector (3292d97f) is absent in en-US and not needed.
- Case folding follows the C locale (ASCII), which matches the engine CRT behaviour. Non-ASCII RegularText was not tested.
