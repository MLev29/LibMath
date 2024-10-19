# LibMath UnitTest Cmake

set (TARGET_NAME UnitTest)

include(FetchContent)

# ~ Catch2
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
	GIT_TAG         v3.7.1 # or a later release
	GIT_SHALLOW		ON
)

set(CATCH_INSTALL_DOCS OFF CACHE BOOL "Install documentation alongside library" FORCE)
set(CATCH_INSTALL_EXTRAS OFF CACHE BOOL "Install extras (CMake scripts, debugger helpers) alongside library" FORCE)

set(TEMP ${CMAKE_FOLDER})
set(CMAKE_FOLDER Catch2)

FetchContent_MakeAvailable(Catch2)

set(CMAKE_FOLDER ${TEMP})

# ~ glm
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG			1.0.1
	GIT_SHALLOW		ON
)

FetchContent_MakeAvailable(glm)

# ~ Sources
file(GLOB_RECURSE TARGET_HEADER_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(GLOB_RECURSE TARGET_SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB_RECURSE TARGET_EXTRA_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.txt
	${CMAKE_CURRENT_SOURCE_DIR}/*.md
)

set(TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES} ${TARGET_EXTRA_FILES})

# generate visual studio filter
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES}) 

set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


# ~ Executable
add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})

target_include_directories(${TARGET_NAME}
	PRIVATE ${TARGET_INCLUDE_DIR}
	PRIVATE ${LIBMATH_INCLUDE_DIR}
	PRIVATE ${glm_SOURCE_DIR}
)

target_link_libraries(${TARGET_NAME} PRIVATE ${LIBMATH_LIBRARY})
target_link_libraries(${TARGET_NAME} PRIVATE Catch2::Catch2)

if(MSVC)
	target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX /Za)
	# /Za disable compiler language extension (https://github.com/g-truc/glm/blob/master/doc/manual.pdf page 44)

	target_link_options(${TARGET_NAME} PRIVATE /FORCE:UNRESOLVED)
	# /FORCE:UNRESOLVED disable compiler LNK2019: unresolved external symbol
else()
	message("Not using MSVC")
endif()