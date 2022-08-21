project(Scene)

add_library(Scene
    Scene.cpp
    Camera.cpp
	Shader.cpp
    Uniforms.cpp
)

add_definitions(-std=c++11)

target_include_directories(${PROJECT_NAME}
    PUBLIC includes
	PUBLIC ../
    PUBLIC ../Loader/includes
    PUBLIC ../Objects/includes
    PUBLIC ../Animator/includes
    PUBLIC ../Physics/includes
	PUBLIC ../_external/glfw/include
	PUBLIC ../_external/glfw/deps
	PUBLIC ../_external/glm
)
