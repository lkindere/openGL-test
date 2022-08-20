project(Objects)

add_library(Objects
    Camera.cpp
    Player.cpp
    Light.cpp
	Shader.cpp
    Uniforms.cpp
    Object.cpp
    Mob.cpp
)

add_definitions(-std=c++11)

target_include_directories(${PROJECT_NAME}
    PUBLIC includes
	PUBLIC ../
    PUBLIC ../Loader/includes
    PUBLIC ../Animator/includes
    PUBLIC ../Physics/includes
	PUBLIC ../_external/glfw/include
	PUBLIC ../_external/glfw/deps
	PUBLIC ../_external/glm
)
