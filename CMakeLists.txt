cmake_minimum_required(VERSION 3.24.0)

project(test)

add_executable(${PROJECT_NAME}
	main.cpp
	${HEADERS}
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(
	MLX_INCLUDES ./MLX/include/MLX42
)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${MLX_INCLUDES}
)


target_link_libraries(${PROJECT_NAME}
	${CMAKE_SOURCE_DIR}/MLX/libmlx42.a
	glfw
)

