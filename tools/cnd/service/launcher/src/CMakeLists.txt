rock_executable(cnd-launcher Main.cpp
    SOURCES
        LaunchAnnotationExtraction.cpp
    HEADERS
        LaunchAnnotationExtraction.hpp     
    DEPS_PKGCONFIG
        cnd-execution-old
    )
