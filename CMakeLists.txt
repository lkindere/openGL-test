cmake_minimum_required(VERSION 3.23.2)

project(test)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_executable(${PROJECT_NAME}
	main.cpp
	callbacks.cpp
)

add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(Objects)

add_definitions(-std=c++11 -DDEBUG)

target_include_directories(${PROJECT_NAME}
	PUBLIC glfw/include
	PUBLIC glfw/deps
	PUBLIC glm
	PUBLIC Objects
)

target_link_directories(${PROJECT_NAME}
	PRIVATE glfw/src
)


target_link_libraries(${PROJECT_NAME}
	glfw
	Objects
)