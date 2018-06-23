cmake_minimum_required(VERSION 3.10)
project(SignalGenerator)

set(CMAKE_CXX_STANDARD 11)

add_library(SignalGenerator SHARED source/SignalGenerator.cpp include/SignalGenerator.hpp)
target_include_directories(SignalGenerator BEFORE PUBLIC include/)

option(BUILD_TEST "Controls whether or not we build the unit tests" OFF)
if(BUILD_TEST)
    add_executable(signalGeneratorTest source/sig.cpp)
    target_link_libraries(signalGeneratorTest SignalGenerator)
endif(BUILD_TEST)
