cmake_minimum_required (VERSION 3.0)

project (refrain)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB_RECURSE file_list
    "${PROJECT_SOURCE_DIR}/src/cu/*.cpp")

add_library(refrain ${file_list})

target_link_libraries (refrain
	floral)

target_include_directories (refrain PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
