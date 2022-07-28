cmake_minimum_required(VERSION 3.23.2)

project(Importer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_executable(${PROJECT_NAME}
	main.cpp
)

add_subdirectory(/Users/lkindere/Desktop/test/external/assimp ./build)

add_definitions(-std=c++11 -DDEBUG)

target_include_directories(${PROJECT_NAME}
	PUBLIC ../external/assimp/include
)

target_link_directories(${PROJECT_NAME}
	PRIVATE ../external/assimp/bin
)


target_link_libraries(${PROJECT_NAME}
	assimp
)