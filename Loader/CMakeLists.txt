cmake_minimum_required(VERSION 3.23.2)

project(Loader)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_library(${PROJECT_NAME}
	Importer.cpp
	ProcessVAO.cpp
	ProcessBones.cpp
	Conversions.cpp
	ArrayObject.cpp
	Bone.cpp
)

add_subdirectory(external/assimp)

add_definitions(-std=c++11)
# add_definitions(-DDEBUG)

target_include_directories(${PROJECT_NAME}
	PUBLIC includes
    PUBLIC ../
	PUBLIC ../Objects/includes
	PUBLIC external/assimp/include
	PUBLIC ../external/glfw/include
	PUBLIC ../external/glfw/deps
	PUBLIC ../external/glm
)

target_link_directories(${PROJECT_NAME}
	PRIVATE external/assimp/bin
)

target_link_libraries(${PROJECT_NAME}
	assimp
)