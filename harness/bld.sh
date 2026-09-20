#!/bin/sh
# bld.sh name  -> builds harness/name.c into name.exe (x64 MSVC)
cmd //c "set PATH=C:\Program Files (x86)\Microsoft Visual Studio\Installer;C:\Windows\System32;%PATH%&& call D:\VisualStudio\BuildTools\VC\Auxiliary\Build\vcvarsall.bat x64 >nul && cd /d D:\llm-experiments\misk\zira\harness && cl /nologo /O2 /W3 $1.c ole32.lib oleaut32.lib sapi.lib /Fe:$1.exe" 2>&1 | grep -v "^$1.c$"
