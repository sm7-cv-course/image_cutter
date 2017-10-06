include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/source")

set (HEADERS
	 common_c.h
	 cscene.h
	 cslidewin.h
	 cslidewin_thread.h
	 cviewer.h)

QT4_WRAP_UI(UISrcs ${CMAKE_CURRENT_SOURCE_DIR}/../form_ui/viewer.ui)

# QT4_WRAP_CPP(MOCSrcs HEADERS)
QT4_WRAP_CPP(MOCSrcs cviewer.h)
QT4_WRAP_CPP(MOCSrcs cscene.h)
QT4_WRAP_CPP(MOCSrcs cslidewin_thread.h)

add_executable (ImageCutter
	            cslidewin_thread.cpp
	            cscene.cpp
	            cslidewin.cpp
	            cviewer.cpp
	            main.cpp
	            ${MOCSrcs} ${UISrcs})

target_link_libraries (ImageCutter ${QTLIBS} ${QT_LIBRARIES})
