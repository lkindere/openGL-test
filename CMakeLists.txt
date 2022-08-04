cmake_minimum_required(VERSION 3.23.2)

project(test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_executable(${PROJECT_NAME}
	main.cpp
	callbacks.cpp
)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_subdirectory(Objects)
add_subdirectory(Importer)

add_definitions(-std=c++17 -DDEBUG)

target_include_directories(${PROJECT_NAME}
	PUBLIC external/glfw/include
	PUBLIC external/glfw/deps
	PUBLIC external/glm
	PUBLIC external/assimp/include
	PUBLIC Objects
	PUBLIC Importer
	PUBLIC Importer/external/assimp
)

target_link_directories(${PROJECT_NAME}
	PRIVATE external/glfw/src
	PRIVATE external/assimp/bin
)


target_link_libraries(${PROJECT_NAME}
	glfw
	assimp
	Objects
	Importer
)