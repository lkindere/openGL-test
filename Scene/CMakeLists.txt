project(Scene)

add_library(Scene
    Camera.cpp
    Scene.cpp
	Shader.cpp
    Uniforms.cpp
    Spawner.cpp
    Terrain.cpp
)

add_definitions(-std=c++11)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC ../main.hpp
    PRIVATE includes/Camera.hpp
    PRIVATE includes/Scene.hpp
    PRIVATE includes/Shader.hpp
    PRIVATE includes/Spawner.hpp
    PRIVATE includes/Uniforms.hpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC includes
	PUBLIC ../
    PUBLIC ../Loader/includes
    PUBLIC ../Objects/includes
    PUBLIC ../Animator/includes
	PUBLIC ../_external/glfw/include
	PUBLIC ../_external/glfw/deps
	PUBLIC ../_external/glm
)
