# 212-Терский-Илья-(Урок 5: модульность, единицы трансляции и библиотеки)

cmake_minimum_required(VERSION 3.12)

project(04.linkage)

add_library(
	calculation

	SHARED

	calculation.cpp
	calculation.h
)

set_target_properties(calculation PROPERTIES
	WINDOWS_EXPORT_ALL_SYMBOLS ON
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
