cmake_minimum_required(VERSION 3.23.2)

project(test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS "-O2")

add_executable(${PROJECT_NAME}
	main.cpp
    debug.cpp
    settings.cpp
	callbacks.cpp
)

add_subdirectory(_external/glfw)
add_subdirectory(_external/glm)

add_subdirectory(Loader)
add_subdirectory(Scene)
add_subdirectory(Animator)
add_subdirectory(Objects)

add_definitions(-std=c++11)
# set(CMAKE_BUILD_TYPE RelWithDebInfo)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC main.hpp
    PRIVATE callbacks.hpp
    PRIVATE debug.hpp
    PRIVATE settings.hpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC Loader/includes
    PUBLIC Scene/includes
    PUBLIC Objects/includes
	PUBLIC _external/glfw/include
	PUBLIC _external/glfw/deps
	PUBLIC _external/glm
)

target_link_directories(${PROJECT_NAME}
	PRIVATE _external/glfw/src
)

target_link_libraries(${PROJECT_NAME}
	glfw
	Loader
    Scene
    Animator
	Objects
)