#include <exception>
#include <iostream>

#include "settings.hpp"
#include "callbacks.hpp"

#include "Shader.hpp"
#include "Light.hpp"

#include "Player.hpp"
#include "Object.hpp"
#include "Mob.hpp"

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
	settings.setGravity(0.01);
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

int main(void) {
    Init();

    Shader shader("Shaders/default.vert", "Shaders/default.frag");
	Shader lightShader("Shaders/light.vert", "Shaders/light.frag");

	Player player("Models/sword.fbx");
	player.setWeapon(new Sword("Models/sword.fbx"));

	Light light("Models/light.fbx");

	Mob mob("Models/bones.fbx");

	Object floor("Models/floor.fbx");

	exit(0);
	light.addTarget(shader);
	player.camera.addShader(shader);
	player.camera.addShader(lightShader);

    while (!glfwWindowShouldClose(settings.window())) {
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		light.draw(lightShader);
		player.input();
		player.draw(shader);
		mob.draw(shader);
		floor.draw(shader);
        glfwSwapBuffers(settings.window());
        glfwPollEvents();
    }
	std::cout << glGetError() << std::endl;
    glfwDestroyWindow(settings.window());
    glfwTerminate();
    return 0;
}
