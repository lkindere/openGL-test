#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Camera.hpp"
#include "EBO.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "callbacks.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int height = 1000;
int width = 1000;
const char* title = "Title";

float vertices[] = {-0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f,
                    0.5f, 0.6f, 0.6f, 0.6f, 0.0f, 0.5f, 0.0f, 0.7f,
                    0.7f, 0.7f, -0.25f, -0.25f, 0.0f, 0.8f, 0.8f, 0.8f,
                    0.25f, -0.25f, 0.0f, 0.9f, 0.9f, 0.9f, 0.0f, 0.25f,
                    0.0f, 1.0f, 1.0f, 1.0f};

GLuint indices[] = {
    0,
    3,
    5,
    3,
    2,
    4,
    5,
    4,
    1,
};

GLFWwindow* Init(){
    if (!glfwInit()) throw(std::runtime_error("GLFW init failure"));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        throw(std::runtime_error("Failed to open window"));
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);
    glViewport(0, 0, width, height);
    glfwSetKeyCallback(window, key_callback);
    glfwSetErrorCallback(error_callback);
	glEnable(GL_DEPTH_TEST);
	return window;
}

int main(void) {
	GLFWwindow* window = Init();
    Shader shader("shaders/default.vert", "shaders/default.frag");
    VAO vao;
    vao.bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.linkAttri(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vao.linkAttri(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float),
                  (void*)(3 * sizeof(float)));
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.activate();
        camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");
        camera.Inputs(window);

        vao.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shader.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
