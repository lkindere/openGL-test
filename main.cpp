#include <exception>
#include <iostream>

#include "callbacks.hpp"

#include "Shader.hpp"
#include "Camera.hpp"
#include "ArrayObject.hpp"

#include "Sword.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int height = 1000;
int width = 1000;
const char* title = "Title";

GLFWwindow* Init() {
    if (!glfwInit()) throw(std::runtime_error("GLFW init failure"));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);			//Mac 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        throw(std::runtime_error("Failed to open window"));
        glfwTerminate();
    }
    glfwSetKeyCallback(window, key_callback);
    glfwSetErrorCallback(error_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL(glfwGetProcAddress);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
	// glDebugMessageCallback(GLdebug_callback, NULL);	//4.3 + 
#if DEBUG > 0
	std::cout << glGetString(GL_VERSION) << 'n' << std::endl;
#endif
    return window;
}

int main(void) {
    GLFWwindow* window = Init();
    Shader shader("shaders/default.vert", "shaders/default.frag");
	Sword sword;
	Camera camera(width, height);	
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.activate();
		camera.Inputs(window);
		camera.updateMatrix(90.0f, 0.1f, 100.0f);
		camera.Matrix(shader, "camPos");
		sword.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	std::cout << glGetError() << std::endl;

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
