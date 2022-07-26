#include <exception>
#include <iostream>

#include "callbacks.hpp"

#include "Shader.hpp"
#include "ArrayObject.hpp"

#include "Sword.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int height = 1000;
int width = 1000;
const char* title = "Title";

std::vector<Vert2v3> vertices =
{
	Vert2v3{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
	Vert2v3{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
	Vert2v3{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}
};

std::vector<GLuint> indices = {
	0, 1, 2
};

GLFWwindow* Init() {
    if (!glfwInit()) throw(std::runtime_error("GLFW init failure"));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
	glDebugMessageCallback(GLdebug_callback, NULL);
#if DEBUG > 0
	std::cout << glGetString(GL_VERSION) << 'n' << std::endl;
#endif
    return window;
}

int main(void) {
    GLFWwindow* window = Init();
    Shader shader("shaders/default.vert", "shaders/default.frag");
	ArrayObject<Vert2v3> obj(vertices, indices);

	Sword sword;
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.activate();
		// obj.bind();
		// glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
		sword.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	std::cout << glGetError() << std::endl;

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
