# Frontend part 2: tree -> prosody -> units/events -> feature matrix (zf2)

Portable C99 port of the second half of the OneCore en-US text frontend (MSTTSEngine_OneCore.dll 10.3.21207,
David / OneCore Zira / Mark). All addresses are VAs in that DLL (base 0x180000000); `loc!` = MSTTSLoc_OneCore.dll.
Status: **bit-exact** against the engine on 749 test lines x 3 voices (feature matrix, per-phone prosody block);
events see the end of this file.

## Files

| file | contents |
|---|---|
| `src/zf2.h` | public API: `zf2_voice_load`, `zf2_run` (stages 1+2), `zf2_features` (stage 3 -> `ZbUtt` of `zb.h`), `zf2_make_events`, `zf2_eval_path` (any feature path), `zf2_process` (all in one) |
| `src/zf2_int.h` | internal tree (`Z2W` word, `Z2S` syllable, `Z2P` phone, phrase / IP / prosodic word) |
| `src/zf2_main.c` | voice INI + engine defaults, `zf_sentence` -> tree conversion, pipeline, debug dump |
| `src/zf2_tree.c` | word predicates, syllabification + phone creation, sentence rebuild with pause insertion, phrase / PW / IP build |
| `src/zf2_prosody.c` | CLinguisticProsodyTagger rules |
| `src/zf2_feat.c` | CTTSFeatureExtractionEngine: path grammar, navigation, getters |
| `src/zf2_units.c` | CTTSUnitGenerator: per-phone prosody block (SAPI rate/pitch/volume/emph), SAPI events |
| `src/zf2_t_dump.c` | test driver: engine dump (stage IN) -> zf2 -> matrix / ctl / events text |
| `harness/zftap2.c` | golden dumper (copy of ziratap ideas): tree at stage IN / PRO / UNIT, per-predictor word fields, matrix, events, phone-converter table, model-runner check |
| `tests/fe2/` | `corpus.txt` (374 lines), `compare.py` (matrix), `compare_ctl.py`, `compare_ev.py`, `view.py`, `ctlview.py`, `feat_<voice>.txt`, `build.sh` |

Build: `sh tests/fe2/build.sh` (MSVC x64 via `src/cl64.bat`); harness: `cmd //c "src\cl64.bat /Fe:..\harness\zftap2.exe ..\harness\zftap2.c ole32.lib sapi.lib"`.
Test: `python tests/fe2/compare.py david|zira|mark [corpus]` then `compare_ctl.py <voice> [corpus]`; events:
`zftap2.exe <voice> @tests/fe2/corpus.txt tests/fe2/out/wave_<voice>.dump` (with audio) then `compare_ev.py <voice>`.

## Input (zf1 boundary) and what zf1 must provide

The zf1 boundary = the utterance after CTextProcessor (handler 0x40000 "after" = 0x80000 "before"). zftap2 dumps it
as stage `IN`. zf2 reads `zf_sentence` (zf.h). Fields added to zf.h for zf2 (zf1 please fill):
- `zf_sentence.quotes` = sentence+0x1e8 list (sentence vt+0x50), records {open word, ?, close word, index} from the
  quote/bracket pairing FUN_1800b8608.
- `zf_sentence.par` = sentence+0x248 list (vt+0x60) of CParallelStruct (FUN_1800b90a8) = list of {word a, word b, type}.
- `zf_word.group` (+0x2e8, grouping object; never seen non-null in 749 lines), `attached_pause` (+0x2b0: pause token
  already inserted after the word; occurs at IN after TN silences +0x214), `ne_obj` (+0x1a8; only matters if
  RatioNameEntities != 100, which no voice sets).
- Already in zf.h and used: type, pos, i180 (punctuation class: 1 `,` 2/3 `;:`-like, 4 `.`, 5 `!`, 6 `?`, 7, 8 = word),
  i210 (silence ms of break tokens), i214 (TN silence), i228, i248, bi/locks, pause class, emph, src_off/len, i2b8
  (last word: pause = SpeakSessionEnd), i2bc (first word of the Speak: leading pause = SpeakSessionStart),
  i2f0/s2f8 (bookmark before the word), fs (fragment: action, emph, silence, prosody floats), the selected
  pronunciation ids (`prons[cur_pron]`, else the phone-name string), sentence type / src_off / src_len.
- The IN tree already contains the sentence-initial pause token (type 3, BI 5, pause 7, i210 = 100 / SpeakSessionStart)
  and SAPI `<silence>` tokens (type 3, fragment action 1).

## Stage 1: CLinguisticProsodyTagger (0x180060010)

**No statistical model runs for David, Zira or Mark (verified at runtime).** The model runners of the break and
emphasis predictors hold one handler each, loc `CProsodyBreakCARTPredictor` / `CProsodyEmphasisCARTPredictor`, but
their "loaded" flag (+0xc) is 0 (no `.BRK`/`.EMP` file), and their run (loc 0x180072c30) returns immediately; the
boundary-tone and pitch-accent runners are empty. `harness/zftap2 ... pred` prints this (`RUNNERS`, `sqcnt`).
All four predictors have +0x20 = 1 (their vt+0x40 post step runs). Order and rules (zf2_prosody.c):

Break predictor pre (0x18009a400):
1. 0x18009afd0 SSML `<break>` tokens: only fragments with the +0x18 flag (SSML path); never for SAPI XML. Not ported.
2. 0x180059964 punctuation / emphasis, per word w with p = previous "real word" (type 0/4 with a pronunciation,
   FUN_180059d0c): punctuation class i180 1/2/3/7: last non-break token -> i228 = 7 and p BI 5 / pause 7; else
   FUN_180073c04: i228 = 1, p BI 4 (if BI < 4, +0x248 == 0, unlocked) and pause 6 (4 if the say-as category is in the
   predictor's list: empty for en-US). Class 4: only at the end (i228 7). Class 5: end -> i228 2, else mid rule.
   Class 6: end -> i228 = 3/5/6/4 for sentence type 1/6/7/other, else mid rule. SAPI emph (fragment +8): 0 -> 0,
   1/2 -> 1 + lock, 3/4 -> 0 + lock. A SAPI `<silence>` token sets BI 4 on the preceding real word.
3. 0x18009ad24 quotes: a pair enclosing > 1 real word and > 3 syllables: open i228 10, close i228 11; the real words
   before the open and before the close (not the last real word) get BI 3, pause 1 (2 if
   SilenceLength.PuncIntermPhraseBoundary is configured, default 10000 = not), BI lock.
4. 0x18009aa04 parallel structures (branch for utterance domains not in engine+0x548, i.e. always here): pause 4 on
   b of every element but the last; last b: BI 3 / pause 1 if BI < 3; real word before the last element's a:
   BI 4 / pause 4 if BI < 4.
5. 0x18009a8b0: the last token with a pronunciation object (skipping breaks / punctuation from the end) gets BI 5,
   pause 7, tone 0x3ea.
6. 0x18009b3e4: +0x214 != 0 -> BI 4, pause 4. 7. 0x18009a808: consecutive words of one +0x2e8 group -> BI 1, +0x248 = 1.
Setters honour the lock words (+0x24c BI, +0x23c tone, +0x258 emphasis); lost call arguments were recovered from
the disassembly (quote close = 11, SSML tone = fragment +0x10, group +0x248 = 1, leading pause class 7).
Break post: domain handlers vt+0x70 (all `return 0`), then loc vt+0x30 = phrase build (redone in stage 2).

Boundary tone pre (0x1800508d4): walking from the first token with a non-empty pronunciation, each token with
i228 != 0 sets the tone of the last pronounced non-break token: i228 1 -> 0x3ea (+0x240 = 5); 2/4/6/7 -> 0x3ea (10);
3/5 -> 0x3ec (10); other (10, 11) -> 0x3eb (5). If any word is emphasised: tone 0 on each emphasised word and its
predecessor. Post (loc CListItemBoundaryToneTaggerEnglish 0x180061530): parallel-structure elements but the last:
b with BI 4 -> 0x3ed, BI 3 -> 0x3e9.
Pitch accent pre (0x180019e70): emphasised real words get +0x22c = 5 (first in the first phrase; 1 for sentence
type 2), 1 (first after a BI > 3 word) or 6, once (+0x230); the first stress-1 syllable's ToBIAccent = +0x22c.
ENU post step loc vt+0x70 (CBoundaryPronChange): no en-US data -> no effect (confirmed by the 100% match).

## Stage 2: CTTSUnitGenerator (0x180034b00)

Sentence vt+0xa0 -> FUN_18001a644 rebuild (the "rebuild" flag +0x60 of the word list is set by the prosody tagger):
- all syllables / phones are rebuilt from the selected pronunciation (FUN_18001aa28): split at ids with flag
  0x40000000 ('&' 1, '-' 2); in each piece (FUN_18001c4ac) ids with flag 0x10000000 or 0x20000000 (stress '1' 5 and
  '2' 6) go to +0x80 of the previous phone (syllable Stress = max(id - 4)), flag 0x80000000 to +0x82, the rest
  become phones. Empty syllables are dropped. The first stress-1 syllable gets ToBIAccent = word +0x22c.
- pause class from BI (FUN_18001afac): BI <= 2 -> 0; 3 -> max(pause, 1); 4 -> keep 3..5, else 3 if the next
  non-break, non-empty token is a word (type 0/4) and 6 otherwise; 5 -> 7.
- silence (FUN_1800199a8): +0x214 if set, else SilenceLength[pause] (x RatioNameEntities/100 inside an entity;
  MSTTS.NoPause zeroes classes 3..6), replaced by SpeakSessionEnd on the last word (i2b8) if non-zero.
- a pause token (FUN_1800777cc: copies the word's fragment, BI, pause class, source offset) is inserted after the word
  unless the next non-empty token is a SAPI `<silence>`; an existing attached pause (+0x2b0) only gets the new length.
- before the first pronounced word, if every phone so far belongs to SAPI `<silence>` tokens, a leading pause token
  (BI 5, pause 7, length SpeakSessionStart on the Speak's first word, else 100) is inserted; it takes over a
  bookmark of the word.
- break tokens get one syllable with one phone: -SP- (4) when [ShortPause] Enable=true (Zira), BI != 5 and not the
  first token; else -SIL- (3).

SilenceLength (ms) by pause class, engine defaults (table 0x18016d790) and INI overrides:

| class | key | default | David | Zira | Mark |
|---|---|---|---|---|---|
| 0 | WordBoundary | 0 | 0 | 0 | 0 |
| 1 | IntermPhraseBoundary | 100 | 0 | 0 | 100 |
| 2 | PuncIntermPhraseBoundary | 10000 | | | |
| 3 | NonPuncIntonationPhraseBoundary | 70 | | | |
| 4 | ParalStructIntonationPhraseBoundary | 120 | | | |
| 5 | ParalStructListIntonationPhraseBoundary | 350 | | | |
| 6 | IntonationPhraseBoundary | 500 | 400 | 250 | 250 |
| 7 | SentenceBoundary | 750 | 750 | 500 | 500 |
| | SpeakSessionStart / End | 100 / 750 | | | |

Sentence vt+0xa8(1) -> FUN_180045c80: phrases end at a word with BI > 2, at the last word, and around break tokens
(which form one-word phrases); leading / trailing tokens without syllables are trimmed (FUN_18004620c / FUN_1800b6688).
Prosodic words (FUN_180045e94) end at BI > 1; intonation phrases (FUN_1800b58ac) at a phrase whose last word has
BI > 3 (break phrases get their own IP).

Per-phone prosody block (phone+0x78, FUN_18005f190; ZbPhoneCtl): {volume, rate, pitch, f32 range, f32 pitch factor,
group ms, pause ms}. Without a SAPI prosody block: {100, 0, 0, 0, 0, 0}. With one (MiddleAdj, RateAdj or Volume set):
rate = round(clamp(RateAdj, -10, 10)), volume = round(clamp(Volume, 0, 150)), pitch = round(clamp(MiddleAdj,
-10, 10)), range 1.0, factor = powf(2, pitch / 24) (0 if 1.0). `<emph>` words (fragment emph 1/2): [Emphasis]
defaults rate 0.8 -> -4, volume 1.2 -> 120, pitch 1.2 -> 4 (FUN_18009ceb0). Pause tokens: pause ms = +0x210.
Rounding = half away from zero (FUN_180074908).

Voice switching: SAPI `<lang langid="409">` makes the OneCore engine render that part with the default voice of the
language (David, 44 features) even under Zira/Mark; the caller must pick the voice per sentence (the test driver
picks it from the engine's matrix width).

## Stage 3: feature extraction (0x18005bfc0 -> 0x180005248)

Every APM feature is a path `Location(.Location)*.Property` (grammar FUN_180037e34; location table 0x18016fee0
{name, level, dir, skip}; property table 0x18016f280). Evaluated for every phone (the phone list includes pause
phones). Navigation: same level = neighbour in the sentence-level list of that level, skipping "empty" nodes when the
location has skip = 1 (Prev/Next of Syllable, Word, ProsodicWord, Phrase, IntonationPhrase; not Prev/NextPhone);
higher level = ancestor; lower level = first / last child. Empty (skip) tests, second vtable slot 1: phone = SIL/SP;
syllable = one silence phone; word (FUN_18001a070) = break, punctuation (type 1), no syllables or empty pron;
phrase = single break word; IP = single break phrase. Getters (per-class tables, see zf2_feat.c) return null on
silence nodes (syllable of one silence phone, break words, break phrases); phone Fw/Bw positions are null on silence
phones; PhoneIdentity never. Counting helpers: word positions / counts count only "real words"; sentence counts
skip silence syllables / break phrases; Fw/BwPosInYesNoQuestion only for sentence type 1, first / last phrase, <= 3.
The per-phone navigation is implemented generically (`zf2_eval_path`), so any path the three APMs use works; the
matrix columns are `zb_feature_path[]` of zb.h (union of the three voices).

## SAPI events (CSAPIEventHandler, unit generator +0xc0; FUN_18009db84)

Per phone, from the phone-converter table (dumped at runtime, 46 entries {id, viseme bytes, SAPI phone ids}):
PHONEME (6) lParam = SAPI id, then VISEME (8) for the first viseme byte and each further non-zero one. wParam low word
= the next phoneme's / viseme's lParam (last: 7 = SAPI silence / 0); the high word (duration ms) comes from the
backend. WORD_BOUNDARY (5) at the first phone of every pronounced non-break word: wParam = +0x274 length, lParam =
+0x270 offset, placed before the phone's phonemes. SENTENCE_BOUNDARY (7) first at the first phone: wParam/lParam =
sentence length / offset. TTS_BOOKMARK (4, engine id 0x40004): wParam = _wtol(name), string = name, attached after
the events of the last phone of the preceding word with syllables (or first at the first phone).

## Results (2026-09-18)

Input = the engine's own stage-IN tree (zftap2 dump) for each sentence; compared field by field.

| test | David | Zira | Mark |
|---|---|---|---|
| feature matrix, tests/fe2/corpus.txt (374 lines) | 374/374 | 374/374 | 374/374 |
| feature matrix, tests/fe1/corpus.txt (375 lines) | 375/375 | 375/375 | 375/375 (2 `<lang>` lines rendered by David) |
| per-phone prosody block, both corpora | 749/749 | 749/749 | 749/749 |
| SAPI events (id, next, lParam, bookmark name, offset grouping), corpus.txt | 374/374 | 374/374 | 374/374 |

MSVC x64 and gcc (ucrt64, -std=c99 -Wall -Wextra -pedantic, no warnings) builds give identical results.
Not exercised by any test line: the +0x2e8 group rule (never non-null), SSML `<break>` (not reachable from SAPI XML),
a first phone that is not silence (event special case), RatioNameEntities != 100.
