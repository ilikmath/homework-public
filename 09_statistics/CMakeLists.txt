# 212-Терский-Илья-(статистические характеристики последовательности)

cmake_minimum_required(VERSION 3.10)

project(statistics CXX)

add_executable(statistics
    src/statistics.cpp
    src/main.cpp
)

target_include_directories(statistics PRIVATE include)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(statistics PRIVATE
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(statistics PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

target_compile_features(statistics PUBLIC cxx_std_17)
