project(Objects)

add_library(Objects
	Camera.cpp
	Shader.cpp
)

add_definitions(-std=c++11 -DDEBUG)

target_include_directories(${PROJECT_NAME}
	PUBLIC ../glfw/include
	PUBLIC ../glfw/deps
	PUBLIC ../glm
)

target_link_directories(${PROJECT_NAME}
	PRIVATE ../glfw/src
)

target_link_libraries(${PROJECT_NAME}
	glfw
)