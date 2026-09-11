# 212-Терский-Илья-(Урок 6: конфигурация и сборка программ с CMake)

cmake_minimum_required(VERSION 3.12)

project(Main VERSION 0.0.6)

configure_file(
        config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

add_executable(sumlib_example main.cpp)
set_target_properties(
        sumlib_example PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_include_directories(
        sumlib_example
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(sumlib_example SumLib::sumLib)
