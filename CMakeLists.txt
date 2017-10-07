cmake_minimum_required(VERSION 3.8)
project(Lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp wav_core.h wav_header.h wav_core.cpp)
add_executable(Lab3 ${SOURCE_FILES})