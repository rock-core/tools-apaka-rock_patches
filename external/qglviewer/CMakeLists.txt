cmake_minimum_required(VERSION 3.5)

project(QGLViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(QGLViewer)

# --- generate pkg config file
configure_file(QGLViewer.pc.in QGLViewer.pc @ONLY)
install(
	FILES ${PROJECT_BINARY_DIR}/QGLViewer.pc
	DESTINATION lib/pkgconfig
)

install(
	FILES QGLViewer/qglviewer.h 
		  QGLViewer/camera.h 
		  QGLViewer/manipulatedFrame.h 
		  QGLViewer/manipulatedCameraFrame.h 
		  QGLViewer/frame.h 
		  QGLViewer/constraint.h 
		  QGLViewer/keyFrameInterpolator.h 
		  QGLViewer/mouseGrabber.h 
		  QGLViewer/quaternion.h 
		  QGLViewer/vec.h 
		  QGLViewer/domUtils.h 
		  QGLViewer/config.h
	DESTINATION include/QGLViewer
)

install(
	FILES QGLViewer/libQGLViewer.so.2.6.3
		  QGLViewer/libQGLViewer.prl
	DESTINATION lib
)

set( legacy_target ${CMAKE_INSTALL_PREFIX}/lib/libQGLViewer.so.2.6.3)

set( legacy_link_0 ${CMAKE_INSTALL_PREFIX}/lib/libQGLViewer.so)
set( legacy_link_1 ${CMAKE_INSTALL_PREFIX}/lib/libQGLViewer.so.2)
set( legacy_link_2 ${CMAKE_INSTALL_PREFIX}/lib/libQGLViewer.so.2.6)

install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${legacy_target} \$ENV{DESTDIR}${legacy_link_0})")
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${legacy_target} \$ENV{DESTDIR}${legacy_link_1})")
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${legacy_target} \$ENV{DESTDIR}${legacy_link_2})")