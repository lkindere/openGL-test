project(Objects)

add_library(Objects
	Mesh.cpp
	Camera.cpp
	Shader.cpp
	VAO.cpp
	VBO.cpp
	EBO.cpp
)

add_definitions(-std=c++17 -DDEBUG)

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