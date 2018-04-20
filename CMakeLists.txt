cmake_minimum_required (VERSION 3.0)

project (clover)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB_RECURSE file_list
    "${PROJECT_SOURCE_DIR}/src/cu/*.cpp")

add_definitions (
	-D_CRT_SECURE_NO_WARNINGS)

if (${ANDROID_BUILD})
	message(STATUS "clover will be built using Android configs")
	add_definitions (
		-DPLATFORM_POSIX)
		
	# platform abi
	if (${ANDROID_ABI} STREQUAL "arm64-v8a")
		message(STATUS "clover Android ABI: arm64")
		add_definitions (
			-DPOSIX64)
	else ()
		message(STATUS "clover Android ABI: arm")
		add_definitions (
			-DPOSIX32)
	endif (${ANDROID_ABI} STREQUAL "arm64-v8a")	
	
else ()
	message(STATUS "clover will be built using Windows configs")
	add_definitions (
		-DPLATFORM_WINDOWS)
endif (${ANDROID_BUILD})
	
add_library(clover ${file_list})

target_link_libraries (clover
	floral
	helich)

target_include_directories (clover PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
