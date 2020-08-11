find_package(Threads)
find_package(Qt4 REQUIRED)

QT4_ADD_RESOURCES(VIZ_RESC ressources.qrc)

add_subdirectory(ext)
include_directories(ext)

rock_library(rock_replay
    SOURCES 
        ReplayHandler.cpp 
        LogTask.cpp
        ReplayGUI.cpp
        ReplayGUIBase.cpp
        ${VIZ_RESC}
    MOC
        ReplayGUI.h
        ReplayGUIBase.h
    HEADERS 
        ReplayHandler.hpp 
        LogTask.hpp
        ReplayGUI.h
        ReplayGUIBase.h
    DEPS_PKGCONFIG 
        orocos_cpp
        pocolog_cpp
        rtt_typelib-${OROCOS_TARGET}
        orocos-rtt-${OROCOS_TARGET}
        orocos-rtt-mqueue-${OROCOS_TARGET}
        orocos-rtt-corba-${OROCOS_TARGET}
        QtCore
        QtGui
        vizkit3d
    DEPS
        span_slider
    UI
        main.ui
)

target_link_libraries(rock_replay pthread)
install(FILES ${CMAKE_BINARY_DIR}/src/ui_main.h DESTINATION include/rock_replay/)



rock_executable(rock-replay2 
    SOURCES
        Main.cpp
    DEPS
        rock_replay
)



