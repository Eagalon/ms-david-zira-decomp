# Makefile for the OneCore voice port. Portable C99; GNU make + gcc/clang.
#   make                 -> ../build/gcc/zb_backtest (and libzb.a)
#   make voice           -> zira_say, the library CLI `zira`, libzira_tts.a / .so and the library test
#   make CC=clang
#   make M32=1           -> 32-bit x86 build (needs -msse2 -mfpmath=sse for IEEE single/double semantics)
# Bit-exactness requires: no FP contraction (-ffp-contract=off), no fast-math, SSE2 math on x86-32.
ifeq ($(origin CC),default)
CC      = gcc
endif
OUT     ?= ../build/gcc
CFLAGS  ?= -O2 -std=c99 -Wall -Wextra -Wno-unused-parameter
CFLAGS  += -ffp-contract=off -fno-fast-math -fno-finite-math-only
ifeq ($(M32),1)
CFLAGS  += -m32 -msse2 -mfpmath=sse
LDFLAGS += -m32
endif
LDLIBS  += -lm

LIBSRC  = zb_apm.c zb_dur.c zb_mlpg.c zb_vocoder.c zb_vocoder_int.c zb_synth.c zb_synth_int.c zb_io.c zb_sonic.c zb_wave.c \
          $(wildcard zb_ratechg.c)
LIBOBJ  = $(LIBSRC:%.c=$(OUT)/%.o)

all: $(OUT)/zb_backtest

$(OUT):
	mkdir -p $(OUT)

$(OUT)/%.o: %.c zb.h zb_internal.h | $(OUT)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)/libzb.a: $(LIBOBJ)
	$(AR) rcs $@ $^

$(OUT)/zb_backtest: $(OUT)/zb_backtest.o $(OUT)/libzb.a
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# ---- the whole voice: text -> zf1 -> zf2 -> zb -> PCM, and the host library (zira_tts.h) ----
FE1SRC  = zf1_ana.c zf1_dat.c zf1_engine.c zf1_frag.c zf1_fst.c zf1_fstpm.c zf1_lex.c zf1_lts.c zf1_modules.c \
          zf1_morph.c zf1_poly.c zf1_pos.c zf1_post.c zf1_pron.c zf1_pron_oov.c zf1_ss.c zf1_tn.c zf1_util.c zf1_wb.c
FE2SRC  = zf2_feat.c zf2_main.c zf2_prosody.c zf2_tree.c zf2_units.c
TTSSRC  = zira_tts.c $(FE1SRC) $(FE2SRC) $(LIBSRC)
TTSOBJ  = $(TTSSRC:%.c=$(OUT)/%.o)

voice: $(OUT)/zira_say $(OUT)/zira $(OUT)/libzira_tts.a $(OUT)/zira_lib_test

$(OUT)/libzira_tts.a: $(TTSOBJ)
	$(AR) rcs $@ $^

$(OUT)/libzira_tts.so: $(TTSSRC) | $(OUT)
	$(CC) $(CFLAGS) -fPIC -shared -DZIRA_BUILD_DLL $^ -o $@ $(LDLIBS)

$(OUT)/zira_say: $(OUT)/zira_say.o $(OUT)/libzira_tts.a
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OUT)/zira: $(OUT)/zira_cli.o $(OUT)/libzira_tts.a
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OUT)/lib_test.o: ../tests/lib/lib_test.c zira_tts.h | $(OUT)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(OUT)/zira_lib_test: $(OUT)/lib_test.o $(OUT)/libzira_tts.a
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS) -pthread

# the library drop for other programs: the shared library, its headers and the CLI
dist: $(OUT)/libzira_tts.so $(OUT)/zira
	mkdir -p $(OUT)/dist
	cp $(OUT)/libzira_tts.so $(OUT)/zira $(OUT)/dist/
	cp zira_tts.h zb.h $(OUT)/dist/
	printf '%s\n' \
	  'Microsoft David, Zira and Mark (Windows OneCore TTS) - portable C port' '' \
	  '  libzira_tts.so   the library: include zira_tts.h and link against it' \
	  '  zira             the command line front end' '' \
	  'No voice data is included. Point --dir at the folder holding M1033David.APM,' \
	  'its .BEP / .INI and MSTTSLocEnUS.dat from your own installation.' > $(OUT)/dist/README.txt
	@echo "dist: $(OUT)/dist"

clean:
	rm -rf $(OUT)

.PHONY: all voice dist clean
