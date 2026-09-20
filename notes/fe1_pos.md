# zf1 fork C: POS tagging, CPolyphony rules, homograph CRFs, RegularText

Port of the POS/homograph part of the OneCore en-US text frontend (MSTTSEngine_OneCore.dll 10.3.21207.0).
Clean-room: decompiles (`decomp/MSTTSEngine_OneCore/_all.c`) and runtime traces only.
All models are read from `MSTTSLocEnUS.dat` at runtime.

Files:
- `src/zf1_pos.h`, `src/zf1_pos.c`: POS table, Brill tagger, CPOSTaggerImpl::Tag, RegularText suffix classes.
- `src/zf1_poly.c`: CPolyphony rule interpreter, the CRF polyphony runtime (vocabulary trie, scoring, pron apply) and the
  pronunciation-list helper `zf1_pron_set`.
- Unit tests:
  - `src/zf1_t_pos.c`: modes `run`, `cand`, `tag`, `full`.
  - `src/zf1_t_poly.c`: RegularText, CPolyphony and CRF, checked against the final engine state.
- Harness: `harness/zftap1_pos.c` (build with `build_zftap1_pos.bat`). It is zftap1 plus vtable hooks:
  - word vt+0xe8 SetPOS (`SETPOS ra=`), vt+0x88 SetPron (`SETPRON`) and vt+0x60 SetType (`SETTYPE`), each logged
    with its caller RVA;
  - CPOSTaggerImpl vt+0 (`TAGIN`/`TAGOUT`);
  - CPosTagger vt+0, which dumps the candidate node chain (`PTIN`/`PTOUT`);
  - CTTSContainerLexicon vt+8, which logs each lookup result together with the entry's attribute sets (`LEX8`);
  - the W lines also carry the word's CRF probability (`f320`, word+0x320).
- Tests: `tests/fe1/pos/`.
  - `run.sh [corpus]`, plus the converters `ptconv.py` and `polyconv.py`.
  - `vtrie.py` enumerates the CRF vocabularies.
  - `polyrules.txt` is a readable dump of all 648 CPolyphony words and 2079 rules.
  - `homo.txt`: 219 homograph and polyphony lines. `prose.txt`: 1500 docstring sentences. `big.txt` = both.

## Results (engine = David, same frontend for OneCore Zira)

| test | tests/fe1/corpus.txt | big.txt (1719 lines) |
|---|---|---|
| Brill core on the engine's candidate chains (PTIN->PTOUT) | 539/539 chains | 1870/1870 |
| candidate POS lists from the lexicon (with LEX8 oracle for the morph lexicon) | 3624/3625 nodes | 21446/21446 |
| CPOSTaggerImpl::Tag on word lists (TAGIN->TAGOUT, oracle) | 583/583 | 1870/1870 |
| same without the oracle (main lexicon only) | - | 1845/1870 |
| RegularText (+0xb8) | 3924/3924 words | 23015/23015 |
| CRF probability (word+0x320), bit-exact float | 37/37 | 329/329 |
| CPolyphony + CRF source/current pron/Prev+NextCharacters | 402/404 sentences | 1716/1719 |

The remaining differences are test artifacts. In each case the word "the" comes before a word whose pronunciation
CPolyphony or the CRF changes later ("St.", "UN", "ups"). The test loads the final state of the sentence, so param 9
sees the next word's final pronunciation instead of the one it had at that point. The one candidate miss ("eightys")
and all 25 chains that need the oracle depend on the CEnMorph morph lexicon (fork A).

## 1. POS ids

A POS id is the attribute id of a leaf in the lexicon attribute tree (`zf1_lex` attrdefs). The 22 main POS come from
resource f81fd1d1/ed1348b2:

| id | name | id | name | id | name |
|---|---|---|---|---|---|
| 3 | noun (NOM) | 18 | num | 35 | prep (ADP) |
| 6 | verb | 21 | vaux (AUX) | 38 | interjection |
| 7 | verbing | 24 | pron | 41 | particle |
| 8 | verbpastp | 25 | whpron | 44 | symbol (punctuation too) |
| 11 | adj | 28 | adv | 47 | listitem |
| 14 | det | 29 | whadv | 48 | possend |
| 15 | whdet | 32 | conj | 49 | contr |
| 50 | unknown | 0xFFFF | none (SIL words, never tagged) | | |

- The POS table (CPOSTag, built by `FUN_18003777c`) has one entry per attribute below "POS". For each entry:
  - `main` is the nearest ancestor-or-self that is in the 22-list (`FUN_1800379ac`).
  - the category index is taken from the name of the top-level ancestor, looked up in the table at 0x1801ba290:
    unknown 0, NOM 1, VER 2, ADJ 3, DET 4, NUM 5, AUX 6, PRO 7, ART 8, ADV 9, CON 10, ADP 11, INT 12, PAR 13, MEW 14,
    AUW 15, SYM 16, OTH 17.
- The POS table methods:
  - vt+0x20 = main (unknown if the id is not in the table);
  - vt+0x28 = "has main";
  - vt+0x30 = "id is itself main";
  - vt+8 = attribute name, or "unknown";
  - vt+0x10 = category;
  - vt+0x38 = unknown id (50).
- Word vt+0xe8 (0x18014b1a0) sets `pos` = id and `tpos` = main(id). The two are equal for every tagged word.
- `zf1_pos_set` implements this.

## 2. Brill vs n-gram: it is a Brill (transformation-based) tagger

- `CPosTagger` (vt 0x180179390) is created with +0x40 = 1 and +0x44 = 0.
- `FUN_18002ef70`, the "1000-line S-T-A-R-T decoder", is the contextual-rule pass. It is not an HMM.
- Evidence:
  - The model 0cb71848 holds only rules: 12-byte records `{u16 template, u16 from, u16 to, i16 arg, u32 strOff}`,
    219 lexical and 1436 contextual. There are no probabilities.
  - The contextual templates are exactly Brill's: PREVTAG, NEXT1OR2TAG, SURROUNDTAG, WDNEXTTAG, LBIGRAM,
    boundary "S-T-A-R-T", ...
  - Porting the rules alone reproduces all 1870 chains.

Tag flow (`zf1_pos_tag` = 0x1800569d0, OOV flag engine+0x4a0==3 is off):
1. Look at every word whose Text is non-empty. At step 5 every token is type 0, punctuation included. A word of
   another type gets a fixed node with text " ", pos 50 and kind 3.
2. A type-0 word keeps a preset pos (≠0xFFFF and ≠50) as kind 3. Otherwise it gets pos 50 and kind 0.
3. The candidate lexicon POS come from the container lexicon. For each attribute set of the entry (in entry order),
   take the last id that has a main POS and is strictly increasing (`FUN_18005b104`). Keep them unique, drop 50. The
   node's list +0x10 holds the mains of these.
4. `FUN_1800621e8` sets the initial tag:
   - no candidates → pos 50, kind 2 (unknown);
   - one candidate → kind 3 (fixed);
   - several → kind 1, pos = first candidate.
5. Lexical rules (`FUN_18003d1e0`) run on the kind-2 nodes, node by node, with all 219 rules in order. A rule applies
   if `from == 0 || from == pos`. The templates are:

   | template | test |
   |---|---|
   | 0x101 | always |
   | 0x102 | first char of word ∈ str |
   | 0x105/6 | word contains str |
   | 0x107/0x10b | str+word is in the lexicon |
   | 0x108/0x10c | word+str is in the lexicon |
   | 0x109/0x10d | strip prefix str, rest is in the lexicon |
   | 0x10a/0x10e | strip suffix str, rest is in the lexicon |
   | 0x10f/0x111 | starts with |
   | 0x110/0x112 | ends with |
   | 0x113/0x115 | next word == str (no next: str == "S-T-A-R-T") |
   | 0x114/0x116 | previous word == str |

   The first rule is `_everyword_` 50→44, so unknown non-letters become symbol.
6. Contextual rules (`FUN_18002ef70`) loop over the rules on the outside and the nodes on the inside, left to right,
   and change nodes in place.
   - A node is skipped if it is kind 3, or if pos ≠ from.
   - For a known word (kind ≠ 2), `to` must be in its candidate list.
   - The window is prev1-3 / next1-3 over all nodes.
   - Word comparisons are case-sensitive on Text.
   - Tag -2 or "S-T-A-R-T" matches the outside of the chain.
   - Two-word templates split str at `arg` (e.g. `STAARTThat`, a data quirk that can never match).
   - Every template's exact boundary behaviour is in `ctx_match()`.
7. `FUN_18005bc60`: a kind-1 node, or a kind-3 node with exactly one candidate, whose tag is not main gets 50.
   Otherwise the tag becomes the first lexicon candidate whose main equals the tag.
8. Write pos/tpos through vt+0xe8.

Where the tagger is called:
- Analyze step 5 on the whole token list.
- Step 7, `0x180018ed4`: once for every TN expansion, on the expansion's word list alone.
  - If the expansion is a single word, that word first gets the original token's pos (vt+0xe8, table engine+0x530),
    so it is fixed.
  - Entity tokens get a preset pos before tagging (`0x1800c4ab4`, RVA c4b9b: mostly 3, some 50/11/18). This is fork B
    or coordinator territory.

Container lexicon (`CTTSContainerLexicon` vt+8 = 0x18001d850):
- It tries the +0x48 domain lexicons, then the priority list: LEX, hot-fix, VOICE_LEX and the CEnMorph morph lexicon.
- The morph lexicon answers inflections and compounds ("barks" [VER verb][NOM noun], "widescreen" [unknown],
  "widescreenly" found).
- `zf1_pos_set_lookup()` must be given fork A's full container lookup. The default is the main lexicon only.

SAPI `<partofsp>`:
- It is not seen by the tagger. The pronouncer `0x180047abc` (RVA 47c9e) sets pos from the fragment's +0x38 after
  tagging.
- Observed mapping: noun 0x1000→3, verb 0x2000→8, modifier 0x3000→11, function 0x4000→32, interjection 0x5000→38,
  unknown 0 → unchanged.

## 3. RegularText (+0xb8): `FUN_18001bf24`, from 0x18005c794 right after Analyze

`zf1_pos_regular` covers every word of the committed sentence, SIL included:
1. RegularText = towlower(Text) (C locale, so ASCII only).
2. If it contains "'" (list 3 of 5554ba64): keep the part from the last "'" on ("doesn't"→"'t", "it's"→"'s").
3. Otherwise, by POS category, if RegularText ends with a suffix of the list, it becomes "-"+suffix:
   - NOM(1): list 0, 27 noun suffixes (ance … ee);
   - ADJ(3): list 1, 15 adjective suffixes;
   - VER(2): list 2 (ing ify ise ize yse yze ed en).

   This is why the dump shows "-tion", "-ed", "-ing" and so on.

## 4. CPolyphony (e849e61b/4a3c699e), `0x1800c9e30` → `0x18001ee6c` → `0x18001efa0`

Layout:
- Header: `+4 nparams (19)`, `+8 nwords (648)`, `+0xc` offset of `int ptype[nparams]` (0 int, 1 string),
  `+0x10` offset of the word table.
- Word table: 16-byte entries `{?, strOff, nRules, rulesOff}`.
- Rule: `{type (1 = string result), resultOff, nCond, condOff}`.
- Condition: `{param, op, valueType, value}`.
- Strings are `u16 len + chars`.

Algorithm:
- The word lookup is a binary search on Text, case-sensitive, shorter-prefix first.
- It applies to type-0 words with frag action 0 or 4 and non-empty text.
- The first rule whose conditions all hold wins.
- Parameters are computed lazily per word and cached.
- The result string (e.g. "dh ih 1") goes through the phone set to ids, then vt+0x88 with source 13, so
  `i278` = 13. An empty result gives an empty pronunciation.

Parameters (`0x1800c9ef0`):
- prev/next mean the neighbour in the word list, skipping type-3 words.
- A "sentence string" is `" w1 w2 … "`: a space before each non-SIL word and a trailing space.

| param | meaning |
|---|---|
| 0 | cur Text |
| 1 / 4 / 7 | case class of cur / prev / next (`0x1800ca5ac`): -1 empty, 5 non-letter, 50 all lower, 30 lower-first mixed, 120 all upper, 110 upper except last, 70 Capitalised, 90 other |
| 2 / 5 / 8 | POS attribute name of cur / prev / next ("unknown" if missing) |
| 3 / 6 | prev / next Text ("" if none) |
| 9 | first letter of the name of the next word's first current phone (phone 0x20 if none) |
| 10 | whole-sentence string |
| 11 | constant int 1 |
| 12 | string of the words before cur |
| 13 | string of the words after cur |
| 17 | separated(prev, cur) |
| 18 | separated(cur, next) |

`separated(a, b)` is `0x1800b7fd8`. It is 1 if both a and b have an NE type, the same src offset and the type is not
"sp:default". Otherwise it is `b.off > a.off + a.len`. A missing word gives 0.

Operators (table 0x18016d530):

| op | test |
|---|---|
| 1-5 | int ==, <, <=, >, >= (param vs value) |
| 6 | equal |
| 7 | starts with |
| 8 | ends with |
| 9 | contains (KMP) |
| 10 | value contains param |
| 11 | equal, case-insensitive |
| 12 | starts with, ci |
| 13 | contains, ci |
| 14 | value contains param, ci |
| 15 | not equal |
| 18 | not equal, ci |
| 19 | not starts with, ci |
| 21 | ends with, ci |

"ci" means ASCII towlower, as in the UCRT C locale.

The same rule-table format and interpreter skeleton (`FUN_18001f36c`, `FUN_18001f970`) is used by the step-9
punctuation typing `0x1800bb3e0` → `0x180060c48` → `0x1800200dc`. That step sets type 1 and +0x180 before CPronouncer,
with a different param evaluator. It belongs to the coordinator, but `zf1_poly.c` can be reused.

## 5. Homograph CRFs (d49f77b9/3e135d7f), `0x180060158`

Bank layout:
- `u32 namePoolOff, u32 modelsBase, u32 n=13, u32 modelOff[n], u32 nameOff[n]`.
- Names: ADDRESS CLOSE COMPLEX CONFLICT CONTRACT LEAD LIVE OBJECT PRESENT READ SUBJECT UPS USE.
- A model is selected by upper-cased Text (ASCII towupper).

Model blob (`0x1800e4f00`):

| offset | contents |
|---|---|
| +0 | "TD\0\0", GUID, u32 size |
| +0x18 | u16 LCID, u16 |
| +0x1c | "CRF\0" |
| +0x20 | u32 100 |
| +0x24 | `{poolOff, poolSize, nLabels, nTemplates, trieSize, weightBytes, 16}`, then float scale (1.0) at +0x40 |
| +0x44 | u32 label offsets, then template offsets (into the pool) |
| then | CVocabTrie (trieSize bytes), float weights (weightBytes + 16 bytes; vocabulary size = weights/8 + 2) |

- The pool is at +poolOff.
- The last 16 bytes of the weights are also used as the bigram block (+0xf0), which these models never use.
- Labels are pronunciations with '%' in place of ' ' (`R%IY%1%D`).
- Templates are CRF++-style unigrams, 12 per model, 24 for CONTRACT and SUBJECT:
  - `U00:Token.PrevToken.PrevToken.PrevToken.CaseInsensitiveText`, …,
    `U11:Token.NextToken…/…/…` (parts joined by "/");
  - CONTRACT and SUBJECT add `Token.PreviousCharacters.GetCharacter(k)` and `NextCharacters.GetCharacter(k)`.
- Token values:
  - CaseInsensitiveText (+0xd8, upper case) of the word at that distance in the word list, punctuation included.
  - Outside the list the value is "_B-1"/"_B-2" (before) or "_B+1"/"_B+2" (after), and "_B" when 3 or more past the
    edge.

CVocabTrie (`0x18003cce0`, lookup `0x18002c5f0`):
- Header u16/u32 counts, then:
  - A: symbol code table;
  - B;
  - C: the "0x80" child-index code table;
  - D: the relative-child code table;
  - E: `{u16 char, u16 flags}` per symbol index;
  - F;
  - G: u32 absolute child offsets;
  - H: u32 relative child deltas;
  - the root at +0x28.
- Symbols use a variable-length cumulative code (`v=b0; while tab[k]<=v: acc+=tab[k]; v=(v-tab[k])*256+b[k+1]`).
- Node flags:

  | flag | meaning |
  |---|---|
  | 1 | terminal |
  | 2 | last sibling (0x200 means continue) |
  | 4 | subtree terminal count follows (1-3 byte varint) |
  | 0x10 | has children |
  | 0x40 | child inline |
  | 0x80 | child through C/G |
  | 0x100 | 3-byte absolute child |
  | 0 | relative child through D/H |

- The feature id is the preorder terminal index. A lookup counts only if the whole key matched.
- The python model is in `vtrie.py` (it enumerates and looks up; lookup was verified against the enumeration).

Scoring and apply:
- score(l) = Σ_templates w[id*nLabels + l], summed as floats in template order; id −1 is skipped. Multiply by scale.
- The sequence is the single target token, so Viterbi reduces to an argmax (the first label wins ties).
- logZ = logadd in double, stored as float: `max + log(exp(min-max)+1)` if min-max > -50.
- p = (float)exp((double)(s_best − logZ)). It is stored in word+0x320 (default 1.0).
- If p > 0.6, the label pronunciation is applied with source 22.
- Words are skipped if type ≠ 0, action not 0/4, or source 13/14 (CPolyphony already decided).
- Before scoring:
  - PreviousCharacters = the last 3 characters of the preceding words' Text, nearest first ("I read" → "I^^");
  - NextCharacters = the first 3 characters of the following words ("the");
  - both are padded with '^'.

Order inside `CPronouncer::Pronounce` (`0x1800479e0`):
1. The 180047abc loop (lexicon / POS pron choice, SAPI POS).
2. The 180047eac loop (OOV / LTS).
3. **CPolyphony** over all words.
4. The RNN polyphony (absent, a no-op).
5. **CRF** over all words.
6. The 180017d1c loop.
7. 1800563dc (final pron pass).

`zf1_poly_apply` = steps 3+5.
- `zf1_pron_set` = CTTSPronunciationList vt+0x18 (0x18004d8d0) + word vt+0x88: select an equal pronunciation, or insert
  it into the sorted (u16) list; make it current; set `i278` unless the source is 0x17; do nothing if `i278` == 0x14.
- It also fills `w->pron` with the phone names. Fork A's final pass may rewrite `pron`.

## 6. Pron source codes seen in i278 (word vt+0x188)

| value | source |
|---|---|
| 1 | lexicon |
| 2 | TN/morph entry |
| 6 / 8 / 9 / 16 / 20 | fork A paths (8 = spelled letters, empty pron for punctuation) |
| 13 | CPolyphony |
| 22 | homograph CRF |
| 23 (0x17) | "keep source" |
