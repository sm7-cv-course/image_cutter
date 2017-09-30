ifdef MYLIB_INCLUDE_DIR
INCLUDE_DIR = $(MYLIB_INCLUDE_DIR)
else
INCLUDE_DIR = $(MYLIB_DIR)
endif

##############################################
######## основные библиотечные файлы #########
##############################################

#source_sift_lib_dir=d:\work\develop_svn\trunk\library\bin\siftlib

#source_adaboost_lib_dir=d:\work\develop\recognition\adaboost_lib_mt
#source_desc_lib_dir=d:\work\develop\recognition\desc_lib_mt

source_adaboost_lib_dir=E:\Shtanov\projects\Classificators\abc\source
source_desc_lib_dir=E:\Shtanov\projects\Classificators\ProducterDeDescripteurs\source

source_mylib_math_dir = $(INCLUDE_DIR)/math
source_mylib_common_dir = $(INCLUDE_DIR)/common

##############################################

#library+= $(source_sift_lib_dir)/lib_siftgpu_cc_10.lib
#library+= $(source_adaboost_lib_dir)/abclib.lib
#library+= $(source_desc_lib_dir)/descripteur.lib

mylib_options_include +=\
						$(opt_inc) "$(source_mylib_common_dir)" \
						$(opt_inc) "$(source_adaboost_lib_dir)" \
						$(opt_inc) "$(source_desc_lib_dir)"
#						$(opt_inc) "$(source_sift_lib_dir)"

##############################################

obj_file+=\
			$(obj_dir)/cslidewin.$(ext_obj) \
			$(obj_dir)/cslidewin_thread.$(ext_obj)

obj_moc_file+=\
	$(obj_dir)/cslidewin_thread_moc.$(ext_obj)


##########################################################################

$(moc_dir)/cslidewin_thread_moc.cpp : $(source_dir)/cslidewin_thread.h
	$(MOC) -o $@ $? 

##########################################################################

$(obj_dir)/cslidewin.$(ext_obj) : $(source_dir)/cslidewin.cpp
	$(command_comp)

$(obj_dir)/cslidewin_thread.$(ext_obj) : $(source_dir)/cslidewin_thread.cpp
	$(command_comp)

$(obj_dir)/cslidewin_thread_moc.$(ext_obj) : $(moc_dir)/cslidewin_thread_moc.cpp
	$(command_comp)	

