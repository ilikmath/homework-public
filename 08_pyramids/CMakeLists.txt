# 212-Терский-Илья-(Задание 8: пирамиды на 2D-плоскости, наследование, STL-список, gnuplot)

cmake_minimum_required(VERSION 3.12)
project(08_pyramids LANGUAGES CXX)

add_executable(pyramids
    main.cpp
)

set_target_properties(pyramids PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_compile_options(pyramids PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wshadow
)
