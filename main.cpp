#include <exception>
#include <iostream>

#include "Mesh.hpp"
#include "callbacks.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int height = 1000;
int width = 1000;
const char* title = "Title";

Vertex vertices[] =
{ //               COORDINATES           /            NORMALS          /         COLORS          //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

GLFWwindow* Init() {
    if (!glfwInit()) throw(std::runtime_error("GLFW init failure"));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
    return window;
}

int main(void) {
    GLFWwindow* window = Init();
    Shader shader("shaders/default.vert", "shaders/default.frag");
    // VAO vao;
    // vao.bind();
    // VBO vbo(vertices, sizeof(vertices));
    // EBO ebo(indices, sizeof(indices));
    // vao.linkAttri(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // vao.linkAttri(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float),
    //               (void*)(3 * sizeof(float)));
    // vao.unbind();
    // vbo.unbind();
    // ebo.unbind();

	Shader light("shaders/light.vert", "shaders/light.frag");
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> inds(indices, indices + sizeof(indices) / sizeof(GLuint));
	Mesh mesh(verts, inds);
	// VAO lvao;
	// lvao.bind();
	// VBO lvbo(lightVertices, sizeof(lightVertices));
	// EBO lebo(lightIndices, sizeof(lightIndices));
	// lvao.linkAttri(lvbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// lvao.unbind();
	// lvbo.unbind();
	// lebo.unbind();

	// glm::vec3 lightPos(0.5f, 0.5f, 0.5f);
	// glm::mat4 lightModel(1.0f);
	// lightModel = glm::translate(lightModel, lightPos);

	// glm::vec4 lightColor(0.0f, 0.0f, 1.0f, 0.0f);

	// glm::vec3 shapePos(0.0f, 0.0f, 0.0f);
	// glm::mat4 shapeModel(1.0f);
	// shapeModel = glm::translate(shapeModel, shapePos);

	// light.activate();
	// glUniformMatrix4fv(glGetUniformLocation(light.getID(), "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	// glUniform4f(glGetUniformLocation(light.getID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	// shader.activate();
	// glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(shapeModel));
	// glUniform4f(glGetUniformLocation(shader.getID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);


    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window)) {
        camera.Inputs(window);
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// mesh.Draw(shader, camera);
        // shader.activate();
        // camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");
        // vao.bind();
        // glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int),
        //                GL_UNSIGNED_INT, 0);

		// light.activate();
		// camera.Matrix(45.0f, 0.1f, 100.0f, light, "camMatrix");
		// lvao.bind();
		// glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // vao.destroy();
    // vbo.destroy();
    // ebo.destroy();
    // shader.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
