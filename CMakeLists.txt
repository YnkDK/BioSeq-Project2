cmake_minimum_required(VERSION 3.2)
project(BioSeq_Project2)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

set(CMAKE_CXX_FLAGS "-O3  -Wall -std=c++0x -march=native")

set(SOURCE_FILES
    main.cpp)

set(ALIGNMENT_ALGS
    src/common.h
    src/utils.h
    src/global_linear.h
    src/global_linear.cpp
    src/global_affine.h
    src/global_affine.cpp
    src/performance.h
    src/performance.cpp)

add_executable(BioSeq_Project2 ${ALIGNMENT_ALGS} src/main.cpp)