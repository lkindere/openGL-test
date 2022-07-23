cmake_minimum_required(VERSION 3.23.2)

project(test)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_executable(${PROJECT_NAME}
	main.cpp
	callbacks.cpp
	Shaders.cpp
	VBO.cpp
	EBO.cpp
	VAO.cpp
)

add_subdirectory(
	glfw
	glm
)

add_definitions(-DDEBUG)

target_include_directories(${PROJECT_NAME}
	PUBLIC glfw/include
	PUBLIC glfw/deps
	PUBLIC glm/
)

target_link_directories(${PROJECT_NAME}
	PRIVATE glfw/src
)


target_link_libraries(${PROJECT_NAME}
	glfw
)