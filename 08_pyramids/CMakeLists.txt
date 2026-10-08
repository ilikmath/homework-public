# 212-Терский-Илья-(пирамиды на 2D-плоскости)

cmake_minimum_required(VERSION 3.12)
project(08_pyramids LANGUAGES CXX)

add_executable(pyramids
    main.cpp
    clusters.cpp
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
