project(Animator)

add_library(Animator
    ArrayObject.cpp
    Animator.cpp
    Hitbox.cpp
    Model.cpp
)

add_definitions(-std=c++11)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC ../main.hpp
    PRIVATE includes/ArrayObject.hpp
    PRIVATE includes/Animator.hpp
    PRIVATE includes/Hitbox.hpp
    PRIVATE includes/Model.hpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC includes
	PUBLIC ../
    PUBLIC ../Loader/includes
    PUBLIC ../Loader/_external/assimp/include
    PUBLIC ../Scene/includes
    PUBLIC ../Objects/includes
	PUBLIC ../_external/glfw/include
	PUBLIC ../_external/glfw/deps
	PUBLIC ../_external/glm
)
