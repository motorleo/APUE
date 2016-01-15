cmake_minimum_required(VERSION 2.6)

project(muduo C CXX)

set(CXX_FLAGS
 -g
 # -DVALGRIND
 # -DMUDUO_STD_STRING
 -DCHECK_PTHREAD_RETURN_VALUE
 -D_FILE_OFFSET_BITS=64
 -Wall
 -Wextra
 -Werror
 # -Wconversion
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 # -std=c++0x
 -rdynamic
 )

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/example)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/example)

#include_directories("~/build/release-install/include")
include_directories("~/muduo/")

link_directories("~/build/release-install/lib")

aux_source_directory(. DIR_SRCS)
add_library(maxiaoda ${DIR_SRCS})

add_executable(test1 ./test.cc)
target_link_libraries(test1 muduo_base muduo_net pthread)
