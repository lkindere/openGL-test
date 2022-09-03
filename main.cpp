#include "settings.hpp"
#include "callbacks.hpp"

#include "Scene.hpp"

Settings settings;

#include "Importer.hpp"
#include "debug.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void Init_settings(){
	settings.setWidth(1000);
	settings.setHeight(1000);
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glDebugMessageCallback(GLdebug_callback, NULL);	//4.3 + 
#if DEBUG > 0
	std::cout << glGetString(GL_VERSION) << '\n' << std::endl;
#endif
}

#include "Spawner.hpp"

Shader* g_hitboxShader;

int main(void) {
    Init();
    Scene scene;
    int defaultShader = scene.loadShader("Shaders/default.vert", "Shaders/default.frag", "Shaders/default.geom");
    std::cout << "DEFAULT SHADER ID: " << defaultShader << std::endl;
    int lightShader = scene.loadShader("Shaders/light.vert", "Shaders/light.frag");
    int hitboxShader = scene.loadShader("Shaders/hitbox.vert", "Shaders/hitbox.frag");
    g_hitboxShader = scene.shader(hitboxShader);
    
    scene.camera().updateProjection();
    int player_model = scene.loadModel("Models/player.fbx");
    int floor_model = scene.loadModel("Models/floor.fbx");
    int mob_model = scene.loadModel("Models/enemy.fbx");
    int light_model = scene.loadModel("Models/light.fbx");
    int sword_model = scene.loadModel("Models/sword.fbx");
    int wall_model = scene.loadModel("Models/wall.fbx");

    int lightID = scene.loadInstance(LIGHT, light_model);
    scene.loadInstance(PLAYER, player_model);
    scene.loadInstance(STATIC, floor_model);
    scene.loadInstance(MOB, mob_model);
    scene.loadInstance(MOB, mob_model);

    scene.player()->setWeapon(new Sword(scene.model(sword_model), &scene, -1));

    for (auto it = scene.oBegin(); it != scene.oEnd(); ++it)
        (*it).second->setShader(defaultShader);
    scene.player()->setShader(defaultShader);
    scene.object(lightID)->setShader(lightShader);

    scene.player()->setCollide(true);
    scene.player()->setName("Player");

    int wallID = scene.loadInstance(STATIC, wall_model);
    scene.object(wallID)->setPosition(10.0f, 0.0f, -10.0f);
    scene.object(wallID)->setCollide(true);
    scene.object(wallID)->setWeight(1.0f);
    int wallID2 = scene.loadInstance(STATIC, wall_model);
    scene.object(wallID2)->setPosition(10.0f, 0.0f, 10.0f);
    scene.object(wallID2)->setCollide(true);
    scene.object(wallID2)->setWeight(1.0f);
    int wallID3 = scene.loadInstance(STATIC, wall_model);
    scene.object(wallID3)->setPosition(-10.0f, 0.0f, 10.0f);
    scene.object(wallID3)->setCollide(true);
    scene.object(wallID3)->setWeight(1.0f);
    int wallID4 = scene.loadInstance(STATIC, wall_model);
    scene.object(wallID4)->setPosition(-10.0f, 0.0f, -10.0f);
    scene.object(wallID4)->setCollide(true);
    scene.object(wallID4)->setWeight(1.0f);

    Spawner spawner(scene.model(mob_model), &scene);
    spawner.setPosition(glm::vec3(0.0f, 20.0f, 0.0f));
    spawner.setRange(glm::vec3(-20.0f, -5.0f, -20.0f), glm::vec3(20.0f, 5.0f, 20.0f));
    // scene.addSpawner(&spawner);

    // int barID = scene.loadObject(DETAIL, "Models/bar.fbx");
    
    std::cout << "Objects: " << scene.nObjects() << std::endl;
    std::cout << "Shader: " << scene.nShaders() << std::endl;

    while (!glfwWindowShouldClose(settings.window())) {
        glm::mat4 rot = glm::rotate(scene.object(wallID)->rotation(), glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rot2 = glm::rotate(scene.object(wallID2)->rotation(), glm::radians(1.5f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rot3 = glm::rotate(scene.object(wallID3)->rotation(), glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rot4 = glm::rotate(scene.object(wallID4)->rotation(), glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f));
        scene.object(wallID)->setRotation(rot);
        scene.object(wallID2)->setRotation(rot2);
        scene.object(wallID3)->setRotation(rot3);
        scene.object(wallID4)->setRotation(rot4);
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.animate();
        if (glfwGetKey(settings.window(), GLFW_KEY_1) == GLFW_PRESS)
            scene.camera().setMode(first_person);
        if (glfwGetKey(settings.window(), GLFW_KEY_2) == GLFW_PRESS)
            scene.camera().setMode(third_person);
        if (glfwGetKey(settings.window(), GLFW_KEY_3) == GLFW_PRESS)
            scene.camera().setMode(detached);
        glfwSwapBuffers(settings.window());
        glfwPollEvents();
    }
	std::cout << glGetError() << std::endl;
    glfwDestroyWindow(settings.window());
    glfwTerminate();
    return 0;
}
