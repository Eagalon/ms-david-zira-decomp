@echo off
set "PATH=C:\Program Files (x86)\Microsoft Visual Studio\Installer;C:\Windows\System32;%PATH%"
if not defined VCINSTALLDIR call "D:\VisualStudio\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul
cd /d %~dp0
cl /nologo /O2 /W3 zftap1_pos.c ole32.lib oleaut32.lib sapi.lib /Fe:zftap1_pos.exe || exit /b 1
