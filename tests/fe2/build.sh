#!/bin/sh
# build build/fe2/zf2_t_dump.exe (MSVC x64 via src/cl64.bat)
cd "$(dirname "$0")/../../src" && mkdir -p ../build/fe2 && \
cmd //c "D:\llm-experiments\misk\zira\src\cl64.bat /nologo /O2 /W3 /Fo..\build\fe2\ /Fe:..\build\fe2\zf2_t_dump.exe zf2_t_dump.c zf2_main.c zf2_tree.c zf2_prosody.c zf2_feat.c zf2_units.c zb_apm.c" 2>&1 | grep -E "error|warning" 
exit 0
