cmake_minimum_required(VERSION 3.23.2)

project(test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_executable(${PROJECT_NAME}
	main.cpp
    settings.cpp
	callbacks.cpp
)

add_subdirectory(_external/glfw)
add_subdirectory(_external/glm)

add_subdirectory(Loader)
add_subdirectory(Animator)
add_subdirectory(Objects)
add_subdirectory(Physics)

add_definitions(-std=c++11 -DDEBUG)
# set(CMAKE_BUILD_TYPE RelWithDebInfo)

target_include_directories(${PROJECT_NAME}
    PUBLIC Loader/includes
    PUBLIC Objects/includes
    PUBLIC Physics/includes
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
    Animator
	Objects
    Physics
)