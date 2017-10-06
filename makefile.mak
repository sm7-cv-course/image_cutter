base_dir=$(BASE_DIR)
include $(MAKE_FOR_SYSTEM)

##############################################

# имя исполняемого файла
app_name=slide_window.exe

# директория с исходными файлами
source_dir=$(base_dir)/source

# директория для объектных файлов
obj_dir=$(base_dir)/obj

# директория для moc-файлов
moc_dir=$(base_dir)/moc

# директория для выполняемого файла
proc_dir=$(base_dir)/exe

# директория с h-файлами оконных форм
source_header_form_dir=$(base_dir)/form_h

# директория с ui-файлами оконных форм
source_form_dir=$(base_dir)/form_ui

# директория с заголовочными файлами
cpp_options_include=$(opt_inc) "$(source_dir)" \
							$(opt_inc) "$(source_header_form_dir)"

# h-файлы с формами для окон
h_file_widget=\
	$(source_header_form_dir)/ui_viewer.h

# объектные файла за исключением moc-файлов
obj_file=\
	$(obj_dir)/main.$(ext_obj) \
	$(obj_dir)/cviewer.$(ext_obj) \
	$(obj_dir)/cscene.$(ext_obj)

# объектные файлы полученные из moc-файлов						
obj_moc_file=\
	$(obj_dir)/cviewer_moc.$(ext_obj) \
	$(obj_dir)/cscene_moc.$(ext_obj)

all:
	$(MAKE) $(opt_make_f) makefile.mak clean
	$(MAKE) $(opt_make_f) makefile.mak program

clean:
	$(command_del) $(base_dir)$(SD)obj$(SD)*.$(ext_obj)
	$(command_del) $(base_dir)$(SD)moc$(SD)*moc.cpp
	$(command_del) $(obj_file)
	$(command_del) $(obj_moc_file)
	$(command_del) $(proc_dir)/$(app_name)

# описание цели "построение приложения"
program :  $(h_file_widget) $(proc_dir)/$(app_name)

# создание h-файлов на основе ui-файлов
$(source_header_form_dir)/ui_viewer.h : $(source_form_dir)/ui_viewer.ui
	$(UIC) -o $@ $?

# создание moc-файлов
$(moc_dir)/cviewer_moc.cpp : $(source_dir)/cviewer.h
	$(MOC) -o $@ $?

$(moc_dir)/cscene_moc.cpp : $(source_dir)/cscene.h
	$(MOC) -o $@ $? 

# исходные файлы

#$(obj_dir)/ccorrelationprocess.$(ext_obj) : $(source_dir)/ccorrelationprocess.cpp
#	$(command_comp)

#$(obj_dir)/ccorrelationprocess_moc.$(ext_obj) : $(moc_dir)/ccorrelationprocess_moc.cpp
#	$(command_comp)

$(obj_dir)/main.$(ext_obj) : $(source_dir)/main.cpp
	$(command_comp)

$(obj_dir)/cviewer.$(ext_obj) : $(source_dir)/cviewer.cpp
	$(command_comp)	

$(source_dir)/cviewer.cpp  : \
		$(source_dir)/cviewer.h
	$(command_touch)	

$(obj_dir)/cscene.$(ext_obj) : $(source_dir)/cscene.cpp
	$(command_comp)	

$(source_dir)/cscene.cpp  : \
		$(source_dir)/cscene.h
	$(command_touch)

# компиляция moc-файлов 
$(obj_dir)/cviewer_moc.$(ext_obj) : $(moc_dir)/cviewer_moc.cpp
	$(command_comp)	

$(obj_dir)/cscene_moc.$(ext_obj) : $(moc_dir)/cscene_moc.cpp
	$(command_comp)	

######################################################

#  подключение дополнительных моделей
include $(base_dir)/makefile_lib.mak

######################################################

# создание приложения с помощью линьковщика
$(proc_dir)/$(app_name) : $(obj_file) $(obj_moc_file) 
	$(command_link)  $(obj_file) $(obj_moc_file) $(library)

