# 212-Терский-Илья-(Задание 2: сборка Hello World из нескольких исходных файлов)

cmake_minimum_required(VERSION 3.12)
project(02_hello_world LANGUAGES CXX)

add_executable(hello_world
    hello_world.cpp
    example.cpp
    example.h
    move_me_out.cpp
    move_me_out.h
)

set_target_properties(hello_world PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_compile_options(hello_world PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wshadow
)
