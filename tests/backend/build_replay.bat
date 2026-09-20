@echo off
rem Build the Sonic / CRateChanger replay tests (x64 MSVC).
setlocal
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not defined VSCMD_VER for /f "usebackq delims=" %%i in (`call "%VSWHERE%" -latest -products * -property installationPath`) do call "%%i\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul
cd /d %~dp0
if not exist ..\..\build\x64 mkdir ..\..\build\x64
cl /nologo /O2 /W3 /fp:precise /D_CRT_SECURE_NO_WARNINGS rc_replay.c ..\..\src\zb_ratechg.c /Fe:..\..\build\x64\rc_replay.exe /Fo..\..\build\x64\ || exit /b 1
