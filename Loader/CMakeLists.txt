cmake_minimum_required(VERSION 3.23.2)

project(Loader)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_library(${PROJECT_NAME}
    Importer.cpp
    Conversions.cpp
    ProcessMesh.cpp
    ldebug.cpp
)

add_subdirectory(_external/assimp)

add_definitions(-std=c++11)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC ../main.hpp
    PRIVATE includes/ldebug.hpp
    PRIVATE includes/Structs.hpp
    PRIVATE includes/Conversions.hpp
    PRIVATE includes/ProcessMesh.hpp
    PRIVATE includes/Importer.hpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ../
	PUBLIC includes
    PUBLIC _external
	PUBLIC _external/assimp/include
	PUBLIC ../_external/glm
)

target_link_directories(${PROJECT_NAME}
	PRIVATE _external/assimp/bin
)

target_link_libraries(${PROJECT_NAME}
	assimp
)