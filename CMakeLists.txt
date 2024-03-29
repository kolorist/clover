# 1. required version
cmake_minimum_required(VERSION 3.20min)

# 2. initial setup
project (clover)

# 3. build commands output
if (${USE_MSVC_PROJECT})
	message (STATUS "MSVC Solution / Project structure will be generated")
endif ()

# 4.1 file listing
if (${USE_MSVC_PROJECT})
	file (GLOB_RECURSE file_list
		LIST_DIRECTORIES false
		"${PROJECT_SOURCE_DIR}/include/*.h"
		"${PROJECT_SOURCE_DIR}/include/*.inl"
		"${PROJECT_SOURCE_DIR}/src/*.cpp")
	file (GLOB_RECURSE unity_build_list
		LIST_DIRECTORIES false
		"${PROJECT_SOURCE_DIR}/src/cu/*.cpp")
	list (REMOVE_ITEM file_list ${unity_build_list})
else ()
	file (GLOB_RECURSE file_list
		LIST_DIRECTORIES false
		"${PROJECT_SOURCE_DIR}/src/cu/*.cpp")
endif ()

# 4.2 exclude file according to platform
if (${TARGET_PLATFORM} STREQUAL "arm64-v8a" OR ${TARGET_PLATFORM} STREQUAL "arm-v7a")
	# nothing, because we use unity build
else ()
	list (REMOVE_ITEM file_list
		"${PROJECT_SOURCE_DIR}/include/clover/adb_output_sink.h"
		"${PROJECT_SOURCE_DIR}/src/adb_output_sink.cpp")
endif ()

# 5. specify target
add_library(clover ${file_list})

# 6. compiling
target_include_directories (clover
	PRIVATE		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
	PUBLIC		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

# 7. linking
target_link_libraries (clover
	floral
	helich)

# 8. misc
if (${USE_MSVC_PROJECT})
	# organize filters
	foreach(_source IN ITEMS ${file_list})
		get_filename_component(_source_path "${_source}" PATH)
		file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
		string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
		source_group("${_group_path}" FILES "${_source}")
	endforeach()
endif (${USE_MSVC_PROJECT})
