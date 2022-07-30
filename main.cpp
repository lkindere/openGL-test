#include <exception>
#include <iostream>

#include "Importer.hpp"

#include "settings.hpp"
#include "callbacks.hpp"

#include "Shader.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "ArrayObject.hpp"

#include "Sword.hpp"
#include "Player.hpp"


#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

Settings settings;
const char* title = "Title";

void Init_settings(){
	settings.setWidth(1000);
	settings.setHeight(1000);
	settings.setMode(free_float);
	settings.setFOV(70.0);
	settings.setNear(0.01);
	settings.setFar(1000.0);
}

void Init() {
	Init_settings();
    if (!glfwInit()) throw(std::runtime_error("GLFW init failure"));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);			//Mac 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
    settings.setWindow(glfwCreateWindow(settings.width(), settings.height(), title, NULL, NULL));
    if (!settings.window()) {
        throw(std::runtime_error("Failed to open window"));
        glfwTerminate();
    }
    glfwSetKeyCallback(settings.window(), key_callback);
    glfwSetErrorCallback(error_callback);
    glfwMakeContextCurrent(settings.window());
    glfwSwapInterval(1);
    gladLoadGL(glfwGetProcAddress);
    glViewport(0, 0, settings.width(), settings.height());
    glEnable(GL_DEPTH_TEST);
	// glDebugMessageCallback(GLdebug_callback, NULL);	//4.3 + 
#if DEBUG > 0
	std::cout << glGetString(GL_VERSION) << 'n' << std::endl;
#endif
}

std::vector<Vert2v3> convert_vertices(std::vector<Model>& meshes){
	std::vector<Vert2v3>	vertices;
	for (auto i = 0; i < meshes[0].vertices.size(); ++i){
		Vert2v3	vert;
		vert.v1 = meshes[0].vertices[i];
		vert.v2 = glm::vec3(0.5f);
		vertices.push_back(vert);
	}
	return vertices;
}

int main(void) {
    Init();
    Shader shader("shaders/default.vert", "shaders/default.frag");
	Shader lightShader("shaders/light.vert", "shaders/light.frag");
	Camera camera;
	camera.addShader(shader);
	camera.addShader(lightShader);

	std::vector<Model> meshes = importer("sword.obj");
	std::vector<Vert2v3> vertices = convert_vertices(meshes);
	Sword sword(vertices, meshes[0].indices);

	meshes = importer("sphere.obj");
	vertices = convert_vertices(meshes);
	Light light(vertices, meshes[0].indices);
	light.addTarget(shader);
    while (!glfwWindowShouldClose(settings.window())) {
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.Inputs();
		camera.Matrix();
		light.draw(lightShader);
		sword.draw(shader);
        glfwSwapBuffers(settings.window());
        glfwPollEvents();
    }
	std::cout << glGetError() << std::endl;
    glfwDestroyWindow(settings.window());
    glfwTerminate();
    return 0;
}
