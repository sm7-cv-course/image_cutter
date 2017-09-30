base_dir=$(BASE_DIR)
include $(MAKE_FOR_SYSTEM)

##############################################

# ��� ������������ �����
app_name=slide_window.exe

# ���������� � ��������� �������
source_dir=$(base_dir)/source

# ���������� ��� ��������� ������
obj_dir=$(base_dir)/obj

# ���������� ��� moc-������
moc_dir=$(base_dir)/moc

# ���������� ��� ������������ �����
proc_dir=$(base_dir)/exe

# ���������� � h-������� ������� ����
source_header_form_dir=$(base_dir)/form_h

# ���������� � ui-������� ������� ����
source_form_dir=$(base_dir)/form_ui

# ���������� � ������������� �������
cpp_options_include=$(opt_inc) "$(source_dir)" \
							$(opt_inc) "$(source_header_form_dir)"

# h-����� � ������� ��� ����
h_file_widget=\
	$(source_header_form_dir)/ui_viewer.h

# ��������� ����� �� ����������� moc-������
obj_file=\
	$(obj_dir)/main.$(ext_obj) \
	$(obj_dir)/cviewer.$(ext_obj) \
	$(obj_dir)/cscene.$(ext_obj)

# ��������� ����� ���������� �� moc-������						
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

# �������� ���� "���������� ����������"
program :  $(h_file_widget) $(proc_dir)/$(app_name)

# �������� h-������ �� ������ ui-������
$(source_header_form_dir)/ui_viewer.h : $(source_form_dir)/ui_viewer.ui
	$(UIC) -o $@ $?

# �������� moc-������
$(moc_dir)/cviewer_moc.cpp : $(source_dir)/cviewer.h
	$(MOC) -o $@ $?

$(moc_dir)/cscene_moc.cpp : $(source_dir)/cscene.h
	$(MOC) -o $@ $? 

# �������� �����

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

# ���������� moc-������ 
$(obj_dir)/cviewer_moc.$(ext_obj) : $(moc_dir)/cviewer_moc.cpp
	$(command_comp)	

$(obj_dir)/cscene_moc.$(ext_obj) : $(moc_dir)/cscene_moc.cpp
	$(command_comp)	

######################################################

#  ����������� �������������� �������
include $(base_dir)/makefile_lib.mak

######################################################

# �������� ���������� � ������� �����������
$(proc_dir)/$(app_name) : $(obj_file) $(obj_moc_file) 
	$(command_link)  $(obj_file) $(obj_moc_file) $(library)

