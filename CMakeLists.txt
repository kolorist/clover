cmake_minimum_required (VERSION 3.0)

project (clover)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB_RECURSE file_list
    "${PROJECT_SOURCE_DIR}/src/cu/*.cpp")

add_definitions (-D_CRT_SECURE_NO_WARNINGS)

add_library(clover ${file_list})

target_link_libraries (clover
	floral)

target_include_directories (clover PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
