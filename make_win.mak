############################################################
# Executable modules and extern libraries for win32
############################################################

CPP=$(CC_BIN_DIR)\cl
LINK=link
MAKE=mingw32-make.exe
MOC=$(QT_DIR_VER)\bin\moc.exe
UIC=$(QT_DIR_VER)\bin\uic.exe

TIFF_DIR="C:/GnuWin32"
#IPPLIB_DIR = "C:/Intel/IPP/5.0/ia32"

GDAL_DIR="C:/gdalwin32-1.4.1"
#GDAL_DIR="C:/warmerda/bld"

#CVLIB_DIR = "C:/Intel/OpenCV_1_0"
#CVLIB_DIR = "c:/Intel/OpenCV_2_3"
#CVLIB_DIR = "C:/Intel/OpenCV_2_1"

# Own library
MYLIB_INCLUDE_DIR = D:/work/develop/library/include/_v0.2
############################################################

# switched flags
#DEBUG=yes
#USE_IPP=yes
#USE_MKL=yes
USE_QT=yes
#USE_CUDA=yes
#USE_GDAL=yes
#USE_LIBTIFF=yes
#USE_OPENCV=yes
#USE_OPENCV_2_3=yes

############################################################
# flags
############################################################
# расширение для объектных файлов
ext_obj=obj

# команда удаления файлов
command_del= rm -f

SD=\\

# знак для задания имени файла в include make
opt_f_b=<
opt_f_e=>

# опция для задания директорий с заголовочными файлами
opt_inc=/I
# опиция f для make
opt_make_f=-f

############################################################
# main windows libraries
############################################################

library=kernel32.lib user32.lib gdi32.lib winspool.lib \
		comdlg32.lib advapi32.lib shell32.lib ole32.lib \
		oleaut32.lib uuid.lib imm32.lib winmm.lib \
		wsock32.lib opengl32.lib glu32.lib

# опиции для компилятора С++  /RTC1 /Qopenmp
ifdef DEBUG
cpp_options=  /EHs /GR /D "WIN32"  /D "DEBUG" /D "_CONSOLE"  /D "WIN32API"  \
				/D "_CRT_SECURE_NO_DEPRECATE"   \
				/D "__MSVC_RUNTIME_CHECKS"  \
				/Zc:wchar_t- /MDd   /Zp16 /RTC1
else
cpp_options=  /EHs /GR /D "WIN32"   /D "_CONSOLE"  /D "WIN32API"  \
				/D "_CRT_SECURE_NO_DEPRECATE"   \
				/D "__MSVC_RUNTIME_CHECKS"  \
				/Zc:wchar_t- /MT  /QaxNPT /Zp16 /Qparallel /Qpar-report1  /Qvec-report1 /Qopenmp
endif
############################################################
#подключение внешних библиотек
include $(base_dir)/makefile_extern_lib.mak

command_comp=$(CPP) /c $(cpp_options) $(cpp_options_include) $(qt_options) $(cpp_options_cuda) $(mylib_options_include) /Fo$@ $?

############################################################

command_touch=touch $@
#command_link=$(LINK) /OUT:$@ /LIBPATH:$(LIBINTEL)  /SUBSYSTEM:console /machine:X86 
#command_link=$(LINK) /OUT:$@ /DEBUG /LIBPATH:$(LIBINTEL)  /SUBSYSTEM:console /machine:X86
#command_link=$(LINK) /OUT:$@ /DEBUG /SUBSYSTEM:console /machine:X86
command_link=$(LINK) /OUT:$@ /SUBSYSTEM:console /machine:X86


