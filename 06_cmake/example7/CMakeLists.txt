# 212-Терский-Илья-(Урок 6: конфигурация и сборка программ с CMake)

cmake_minimum_required(VERSION 3.12)

project(example7 VERSION 0.0.3)

option(BUILD_EXAMPLES "Whether to build an examples or not." OFF)

add_subdirectory(src)

if(BUILD_EXAMPLES)
    add_subdirectory(example)
endif()