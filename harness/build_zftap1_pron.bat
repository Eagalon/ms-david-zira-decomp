@echo off
rem Build zftap1_pron.exe (64-bit MSVC).
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not defined VCINSTALLDIR call :findvs
cd /d %~dp0
cl /nologo /O2 /W3 zftap1_pron.c ole32.lib oleaut32.lib sapi.lib /Fe:zftap1_pron.exe || exit /b 1
goto :eof

:findvs
for /f "usebackq delims=" %%i in (`call "%VSWHERE%" -latest -products * -property installationPath`) do call "%%i\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul
goto :eof
