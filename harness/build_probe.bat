@echo off
rem Build ziraprobe.exe (x64). Usage: build_probe.bat
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not defined VCINSTALLDIR for /f "usebackq delims=" %%i in (`call "%VSWHERE%" -latest -products * -property installationPath`) do call "%%i\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul
cd /d %~dp0
cl /nologo /O2 /W3 ziraprobe.c ole32.lib sapi.lib || exit /b 1
