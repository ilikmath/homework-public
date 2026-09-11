# 212-Терский-Илья-(Урок 6: конфигурация и сборка программ с CMake)

cmake_minimum_required(VERSION 3.12)

project(Main VERSION 0.0.5)

configure_file(
        config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

add_executable(library_example main.cpp)
set_target_properties(
        library_example PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_include_directories(
        library_example
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(
        library_example
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)
target_link_libraries(library_example lib)
