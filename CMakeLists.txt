cmake_minimum_required(VERSION 3.6)
project(SOM)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE         -O3 -DNDEBUG)
set(SOURCE_FILES
        constants.h
        deviation.c
        deviation.h
        functions.c
        functions.h
        main.c
        main.h
        montecarlo.c
        montecarlo.h
        setConfiguration.c
        setConfiguration.h
        updates.c
        updates.h)

add_executable(SOM ${SOURCE_FILES})