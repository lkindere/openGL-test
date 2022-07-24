project(Objects)

add_library(Objects
	Camera.cpp
	Shader.cpp
	VAO.cpp
	VBO.cpp
	EBO.cpp
)

add_definitions(-DDEBUG)

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