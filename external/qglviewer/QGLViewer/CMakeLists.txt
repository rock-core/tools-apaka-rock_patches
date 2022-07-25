find_program(QMAKE-QT4 qmake-qt4)

message(STATUS "${CMAKE_HOME_DIRECTORY}")

if (QMAKE-QT4)
    message(STATUS "\t generating Makefile using qmake-qt4") 
    execute_process(
        WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
        COMMAND qmake-qt4 PREFIX=${CMAKE_INSTALL_PREFIX}
        OUTPUT_QUIET
    )

    message(STATUS "\t building library (this may take some time...)")
    execute_process(
        WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
        COMMAND make install
        OUTPUT_QUIET
    )      
else(QMAKE-QT4)
    message(FATAL_ERROR "\t there is no qmake-qt4")  
endif(QMAKE-QT4)