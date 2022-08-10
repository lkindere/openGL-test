project(Animator)

add_library(Animator
    ArrayObject.cpp
)

add_definitions(-std=c++11)

target_include_directories(${PROJECT_NAME}
    PUBLIC includes
	PUBLIC ../
    PUBLIC ../Loader/includes
    PUBLIC ../Loader/_external/assimp/include
    PUBLIC ../Objects/includes
	PUBLIC ../_external/glfw/include
	PUBLIC ../_external/glfw/deps
	PUBLIC ../_external/glm
)
