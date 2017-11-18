cmake_minimum_required(VERSION 3.8)
project(Lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/WAVHeader.cpp headers/WAVHeader.h src/WAV.cpp headers/WAV.h headers/exceptions.h src/exceptions.cpp)
add_executable(Lab3 ${SOURCE_FILES})