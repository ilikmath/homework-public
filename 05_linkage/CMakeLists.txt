# 212-Терский-Илья-(Урок 5: модульность, единицы трансляции и библиотеки)

cmake_minimum_required(VERSION 3.12)

project(04.linkage)

add_executable(
	file_io
	file_io.cpp
)
set_target_properties(file_io PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(
	function_overloading
	function_overloading.cpp
)
set_target_properties(function_overloading PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(
	compilation
	compilation.cpp
	compilation.h
)
set_target_properties(compilation PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)
if (MSVC)
#	target_compile_options(compilation PRIVATE
#		/P
#	)

# /FA Assembly code; .asm
# /FAc Machine and assembly code; .cod
# /FAs Source and assembly code; .asm
# /FAcs Machine, source, and assembly code; .cod
#	target_compile_options(compilation PRIVATE
#		/FAcs
#	)
endif()


add_executable(
	translation_units
	translation_unit1.cpp     # 2 TU
	translation_unit2.cpp     # 3 TU
	translation_unit_main.cpp # 1 TU
)
set_target_properties(translation_units PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)


add_subdirectory(static_library)
add_subdirectory(dynamic_library)


add_executable(
	static_library_usage
	static_library_usage.cpp
)
set_target_properties(static_library_usage PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)
target_include_directories(
	static_library_usage
	PRIVATE
	${CMAKE_SOURCE_DIR}/static_library
)
target_link_libraries(
	static_library_usage
	PRIVATE
	datetime
)

add_executable(
	dynamic_library_usage
	dynamic_library_usage.cpp
)
set_target_properties(dynamic_library_usage PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)
target_include_directories(
	dynamic_library_usage
	PRIVATE
	${CMAKE_SOURCE_DIR}/dynamic_library
)
target_link_libraries(
	dynamic_library_usage
	PUBLIC
	calculation
)
