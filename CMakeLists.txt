cmake_minimum_required(VERSION 3.6)
project(SOM)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE -O3 -DNDEBUG)
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
target_link_libraries(SOM m)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
export OMP_NUM_THREADS=12