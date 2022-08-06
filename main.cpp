#include <exception>
#include <iostream>

#include "settings.hpp"
#include "callbacks.hpp"

#include "Shader.hpp"
#include "Light.hpp"

#include "Player.hpp"
#include "Object.hpp"
#include "Mob.hpp"

#include "Importer.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

Settings settings;
Camera camera;

void Init_settings(){
	settings.setWidth(1000);
	settings.setHeight(1000);
	settings.setGravity(0.01);
    camera.updateProjection();
}

void Init() {
	Init_settings();
    if (!glfwInit()) throw(std::runtime_error("GLFW init failure"));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);			//Mac 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
    settings.setWindow(glfwCreateWindow(settings.width(), settings.height(), "Title", NULL, NULL));
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
	Uniforms uniDefault;
	uniDefault.vec3 = {
		std::make_pair("pos", glm::vec3(0.0f)),
		std::make_pair("scale", glm::vec3(1.0f)),
		std::make_pair("fOffset", glm::vec3(0.0f))
	};
	uniDefault.mat4 = {
		std::make_pair("camPos", glm::mat4(1.0f)),
		std::make_pair("rotation", glm::mat4(1.0f)),
		std::make_pair("fRotation", glm::mat4(1.0f))
	};
    Shader shader("Shaders/default.vert", "Shaders/default.frag", uniDefault);

	Uniforms lightDefault;
	lightDefault.vec3 = {
		std::make_pair("pos", glm::vec3(0.0f)),
		std::make_pair("scale", glm::vec3(1.0f))
	};
    lightDefault.vec4 = {
        std::make_pair("lightColor", glm::vec4(1.0f))
    };
	lightDefault.mat4 = {
		std::make_pair("camPos", glm::mat4(1.0f))
	};
	Shader lightShader("Shaders/light.vert", "Shaders/light.frag", lightDefault);

	Player player(importer("Models/sword.fbx"));
	Light light(importer("Models/light.fbx"));
	Object floor(importer("Models/floor.fbx"));
	Mob mob(importer("Models/bones.fbx"));

	player.setWeapon(new Sword(importer("Models/sword.fbx")));

	light.addTarget(shader);

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
