#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "EBO.hpp"
#include "Shaders.hpp"
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

float vertices[] = {-0.5f, -0.5f,  0.5f,   0.5f,   0.5f, 0.5f, 0.5f, -0.5f,
                    0.5f,  0.6f,   0.6f,   0.6f,   0.0f, 0.5f, 0.0f, 0.7f,
                    0.7f,  0.7f,   -0.25f, -0.25f, 0.0f, 0.8f, 0.8f, 0.8f,
                    0.25f, -0.25f, 0.0f,   0.9f,   0.9f, 0.9f, 0.0f, 0.25f,
                    0.0f,  1.0f,   1.0f,   1.0f};

GLuint indices[] = {
    0, 3, 5, 3, 2, 4, 5, 4, 1,
};

int main(void) {
    if (!glfwInit()) throw(std::runtime_error("GLFW init failure"));

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    Shaders shader("shaders/default.vert", "shaders/default.frag");
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

    GLuint uniID = glGetUniformLocation(shader.getID(), "scale");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.activate();

        glm::mat4 model(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 proj(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)width / height,
                                0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shader.getID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(shader.getID(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projLoc = glGetUniformLocation(shader.getID(), "proj");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(proj));

        glUniform1f(uniID, 0.5f);
        vao.bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
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
