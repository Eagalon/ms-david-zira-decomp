# Microsoft David, Zira and Mark in portable C

A reconstruction of the **Windows OneCore text-to-speech engine** (`MSTTSEngine_OneCore.dll` 10.3, the voices
Windows 8, 10 and 11 ship) in plain C99. It reads the **original voice files** and produces **exactly the same
audio as the real engine**, sample for sample, from text in to 16 kHz PCM out. No Windows, no SAPI, no COM.

No Microsoft code or data is included. The C was written from a disassembly and decompilation of the engine
DLLs and checked stage by stage against the running engine.

**The voice data is not included.** You need your own Windows install: `M1033David.{APM,BEP,INI}` (and/or
`M1033Zira.*`, `M1033Mark.*`) plus the shared `MSTTSLocEnUS.dat` from
`C:\Windows\Speech_OneCore\Engines\TTS\en-US`.

Unlike Microsoft Sam (a formula voice) or Microsoft Anna (5.5 hours of recordings), these voices are
**statistical**: a trained model of a few megabytes predicts the pitch, timing and spectrum of every 5 ms of
speech, and a vocoder turns that into sound. Nothing here is a recording of anyone.

## Status

| stage | source | verified against the real engine |
|---|---|---|
| text processing: sentence splitting, word breaking, FST text normalization, POS tagging (Brill), lexicon, letter-to-sound (CART), morphology, homograph CRFs, polyphony | `src/zf1_*.c` | 375/375 corpus, 1200/1200 prose, 1131/1131 edge cases, 600/600 SAPI XML, 600/600 sentence-split stress, 1500/1500 character fuzz |
| prosody (rules), syllables, pauses, unit and event generation, the acoustic feature table | `src/zf2_*.c` | 749/749 lines x 3 voices: every feature cell, per-phone control and SAPI event |
| acoustic model: APM/BEP loaders, decision trees, state durations, MLPG, voicing, F0 | `src/zb_apm.c`, `zb_dur.c`, `zb_mlpg.c`, `zb_synth*.c` | 140/140 sentences x 3 voices, every intermediate stage |
| vocoder: LSF sharpening, pulse/noise excitation, LPC synthesis, rate change | `src/zb_vocoder*.c`, `zb_wave.c`, `zb_sonic.c`, `zb_ratechg.c` | bit-exact |
| **end to end, text -> WAV** | `zira_say`, `zira` | **David 375/375, Mark 375/375, Zira 373/375** bit-exact (the 2 are `<lang>` lines, see below) |

Two numeric paths: David runs in floating point, Zira and Mark in fixed point, with quantized models and
integer maths. Identical results from MSVC x64, MSVC x86 and gcc.

## Building

```
src\build.bat x64          (MSVC; x86 and "all" work too; output in build\<arch>\)
make voice                 (Linux / macOS / MinGW)
```

Floating point must stay exact: never `-ffast-math`, keep `-ffp-contract=off`.

Windows builds produce **`zira_tts.dll`** with its import library, and `build\<arch>\dist\` collects the
DLL, the `.lib`, the headers (`zira_tts.h` is the one to include) and the CLI — everything another program
needs. On other platforms `make dist` does the same with `libzira_tts.so`.

`python tools/make_portable.py --voices David Zira Mark` goes one step further and writes
`build\<arch>\portable\`: the same drop with a copy of your own voice data beside it and a launcher that
points at it, so the folder runs on a machine with no voices installed. The data in it is Microsoft's, so
keep that folder to your own machines.

## Running

```
build\x64\zira.exe --voice David "Hello, my name is David." out.wav
build\x64\zira.exe --voice Zira --rate 3 --events @story.txt story.wav
build\x64\zira.exe --voice Mark --emotion happy "This is the hidden happy setting." happy.wav
```

`--dir` points at the voice folder (default `C:/Windows/Speech_OneCore/Engines/TTS/en-US`).
`zira_say` is the plain verification front end; `zira` is the library's CLI.

### Emotions

Every voice file carries `[EmotionRecipe]` settings for **happy, sad and angry** (rate, pitch, pitch-range and
volume percentages) that Windows never plays: SAPI and WinRT both strip the `mstts:` tags that would select
them, so the real engine always speaks neutrally. `src/zb.h` documents where each percentage enters the
pipeline. Roughly: happy raises the pitch about 20% and widens the melody by two thirds, sad drops the pitch
about 20% and slows down by a quarter, angry mostly gets louder. **These are implemented from the decompiled
code and cannot be checked against the engine**, because the engine cannot be made to speak them.

## Library (for screen readers and other programs)

`src/zira_tts.h` is the interface; the build also produces `zira_tts.dll` (and `libzira` via the Makefile).

```c
zira_tts *t = zira_tts_open("C:/Windows/Speech_OneCore/Engines/TTS/en-US", "David", err, sizeof err);
zira_tts_set_rate(t, 3);                          /* -10..10 like SAPI; 11..20 for fast listening */
zira_tts_speak(t, "Hello world.", 0, &callbacks); /* blocks; streams PCM and events */
zira_tts_cancel(t);                               /* from any thread, stops within one chunk */
```

Audio (16 kHz, 16-bit mono) streams through a callback as it is produced. Events: sentence and word starts
(byte offsets into the UTF-8 text, with the audio position), `<bookmark mark="..."/>` for index marks, and end.
With `ZIRA_SPEAK_XML` the text may use SAPI XML: `<pitch>`, `<rate>`, `<volume>`, `<emph>`, `<silence>`,
`<spell>`, `<bookmark>`, `<lang>`, `<context>`. Our Microsoft Sam and Anna ports expose the same shape
(`sam_tts.h`, `anna_tts.h`), so one host can drive all of them.

## Notes and oddities

- **`<lang langid="409">`**: SAPI hands the tagged text to the first voice of that language with the *same
  gender*. Mark switches to David (reproduced here); a female voice lands on "Microsoft Zira **Desktop**", the
  older engine that is not ported, which is why two Zira lines differ. It depends on which voices are installed.
- **Zira asks questions**: only she adds a rising pitch ramp on the last syllable of a yes/no question. The flag
  that triggers it lives on the `?` itself, a word with no sound.
- **Phone numbers** are spoken at 80% speed by Zira and Mark, per their `[Domain]` settings.
- **The engine reads one byte from the wrong place** in every LSF model record, overlapping the previous field.
  Reproduced as-is, because the voices are tuned around it.
- **No prosody models run** for David, Zira or Mark: the break, tone and accent models ship only with Eva
  (Cortana's voice). All their prosody is rules.
- **Randomness** is fixed: the vocoder's noise generator is re-seeded with the same constant for every
  utterance, so the output is repeatable.

## Repository layout

- `src/` – the engine: `zf1_*` text processing, `zf2_*` prosody and features, `zb_*` acoustics and vocoder,
  `zira_tts.*` library, `zira_cli.c` and `zira_say.c` front ends. A few tables (`zf1_ss_tab.h`,
  `zf1_morph_tab.h`, `zb_voctab*.h`) are generated from the original DLLs by scripts in `tools/`.
- `notes/` – how every stage works, with addresses in the original DLLs (backend, paramgen, vocoder, io,
  frontend, fe1, fe2, and the sub-notes for sentence splitting, normalization, POS and pronunciation).
- `harness/` – programs that load the real engine, hook it and dump its internal structures for comparison.
- `tools/` – python parsers and helpers (APM/BEP, the language data file, disassembly aids), plus
  `voc_analyze.py` / `voc_compare.py`: analyse any 16 kHz recording into this vocoder's parameters
  (LSFs, F0, gain), resynthesize it with `src/zb_vocode_test.c`, and score the result. Useful for
  hearing what the vocoder does to a voice that was never trained for it.
- `tests/` – input corpora and comparison scripts per stage (reference outputs come from the harnesses).

## License

MIT for the code in this repository (see `LICENSE`). The voices and the original engine are Microsoft's and are
not included.
