
rem set CC_BIN_DIR=E:\msvc2008\VC\bin
rem call %CC_BIN_DIR%\VCVARS32.BAT

set CC_BIN_DIR=C:/VS2008/VC/bin
call %CC_BIN_DIR%/VCVARS32.BAT

rem set QT_DIR_VER=E:\Qt_4\4_7_1
rem set path=%path%;%QT_DIR_VER%\bin;

rem set QT_DIR_VER=C:/Qt/4.7.1
rem set QT_DIR_VER=E:/Qt/4.7.1_
set QT_DIR_VER=C:/qt/4.8.5
call %QT_DIR_VER%/bin/qtvars.bat

rem set CUDA_DIR=E:/NVIDIA/CUDA/v5.0
rem set path=%path%;%CUDA_DIR%/open64/bin;%CUDA_DIR%/bin;%CUDA_DIR%/open64/lib;%CUDA_DIR%/nvvm;

rem set path=%path%;d:/work/develop_svn/trunk/recognition/adaboost_lib; d:/work/develop_svn/trunk/recognition/desc_lib;
set path=%path%;E:/Shtanov/projects/Classificators/abc/source;

echo %path%
call exe\slide_window.exe
