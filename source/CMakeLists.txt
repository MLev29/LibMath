# LibMath Source CMake

set(TARGET_NAME LibMath)

# Get all header files recursively
file(GLOB_RECURSE TARGET_HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

# Get all source files recursively
file(GLOB_RECURSE TARGET_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# Get all misc files recursively
file(GLOB_RECURSE TARGET_EXTRA_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.txt
	${CMAKE_CURRENT_SOURCE_DIR}/*.md
)

set(TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES} ${TARGET_EXTRA_FILES})

# Create Visual Studio filters
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES})

add_library(${TARGET_NAME})
target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})

target_include_directories(${TARGET_NAME} 
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/private
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/public/LibMath
)

set(LIBMATH_LIBRARY ${TARGET_NAME} PARENT_SCOPE)
set(LIBMATH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/public PARENT_SCOPE)

# Set compiler warning level if using MSVC
if (MSVC)
	target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
	message(STATUS "Using MSVC - target_compile_options for ${TARGET_NAME} set")
else()
	message("Not using MSVC - target_compile_options for ${TARGET_NAME} not set")
endif()