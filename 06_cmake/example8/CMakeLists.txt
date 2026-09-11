# 212-Терский-Илья-(Урок 6: конфигурация и сборка программ с CMake)

cmake_minimum_required(VERSION 3.12)

project(example8)

set(SOURCES
        main.cpp
        math.cpp
)

set(HEADERS
        math.h)

add_executable(main ${SOURCES} ${HEADERS})
set_target_properties(
        main PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
)
target_compile_features(
        main
        PRIVATE
        cxx_generic_lambdas
)