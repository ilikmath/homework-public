# 212-Терский-Илья-(Урок 6: конфигурация и сборка программ с CMake)






cmake_minimum_required(VERSION 3.12)

project(Example1)

add_executable(helloWorld main.cpp)

set_target_properties(
        helloWorld PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
)