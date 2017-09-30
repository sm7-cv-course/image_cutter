rem set CC_BIN_DIR=E:\msvc2008\VC\bin
rem call %CC_BIN_DIR%\VCVARS32.BAT

rem set CC_BIN_DIR=C:/VS2008/VC/bin
 set CC_BIN_DIR=C:\MSVS\2010\VC\bin
call %CC_BIN_DIR%/VCVARS32.BAT

rem set QT_DIR_VER=E:\Qt_4\4_7_1
rem call %QT_DIR_VER%\bin\qtvars.bat

rem set QT_DIR_VER=C:/Qt/4.7.1
set QT_DIR_VER=C:/qt/4.8.5
call %QT_DIR_VER%/bin/qtvars.bat

set BASE_DIR=%CD%

rem set CUDA_DIR=E:/NVIDIA/CUDA/v5.0
rem rem set path=%path%;%CUDA_DIR%/open64/bin;%CUDA_DIR%/bin;%CUDA_DIR%/open64/lib;
rem set path=%path%;%CUDA_DIR%/open64/bin;%CUDA_DIR%/bin;%CUDA_DIR%/open64/lib;%CUDA_DIR%/nvvm;

echo %path%

rem nmake  /A /F makefile.mak /E MAKE_FOR_SYSTEM=make_win.mak all
rem mingw32-make.exe  -f  makefile.mak program -e MAKE_FOR_SYSTEM=make_win.mak %1
rem mingw32-make.exe  -f  makefile.mak all -e MAKE_FOR_SYSTEM=make_win.mak %1
C:/mingw/make/bin/mingw32-make.exe -f  makefile.mak all -e MAKE_FOR_SYSTEM=make_win.mak %1

