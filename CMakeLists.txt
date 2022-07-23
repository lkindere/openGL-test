cmake_minimum_required(VERSION 3.23.2)

project(test)

add_executable(${PROJECT_NAME}
	main.cpp
)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(
)

target_include_directories(${PROJECT_NAME}
)


target_link_libraries(${PROJECT_NAME}
	glfw
)

