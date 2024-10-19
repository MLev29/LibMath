# LibMath Root CMake

cmake_minimum_required(VERSION 3.24 FATAL_ERROR) # PATH_EQUAL

# Get project name
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Set CMAKE version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(${PROJECT_NAME})

add_subdirectory(source)
add_subdirectory(unitTest)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})
endif()