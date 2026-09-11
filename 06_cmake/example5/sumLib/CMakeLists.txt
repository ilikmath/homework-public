# 212-Терский-Илья-(Урок 6: конфигурация и сборка программ с CMake)

cmake_minimum_required(VERSION 3.12)

project(SumLibrary VERSION 0.0.3)

configure_file(
        config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

add_library(sumLib STATIC sumLib.cpp sumLib.h)
add_library(SumLib::sumLib ALIAS sumLib)
set_target_properties(
        sumLib PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_include_directories(
        sumLib
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS sumLib EXPORT sumLibTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include
)
install(FILES sumLib.h DESTINATION include)

install(EXPORT sumLibTargets
        FILE sumLibConfig.cmake
        NAMESPACE SumLib::
        DESTINATION lib/cmake/SumLib
)
