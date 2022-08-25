project(Objects)

add_library(Objects
    Player.cpp
    Light.cpp
    Object.cpp
    Mob.cpp
    ../Scene/Uniforms.cpp
)

add_definitions(-std=c++11)

target_precompile_headers(${PROJECT_NAME}
    PRIVATE includes/Object.hpp
    PRIVATE includes/Light.hpp
    PRIVATE includes/Mob.hpp
    PRIVATE includes/Player.hpp
    PRIVATE includes/Sword.hpp
    PRIVATE includes/Weapon.hpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC includes
	PUBLIC ../
    PUBLIC ../Loader/includes
    PUBLIC ../Scene/includes
    PUBLIC ../Animator/includes
	PUBLIC ../_external/glfw/include
	PUBLIC ../_external/glfw/deps
	PUBLIC ../_external/glm
)
