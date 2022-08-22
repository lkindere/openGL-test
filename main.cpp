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
	// settings.setGravity(0.1);
    // camera.updateProjection();
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
	std::cout << glGetString(GL_VERSION) << '\n' << std::endl;
#endif
}

Uniforms default_uniforms(){
    Uniforms uniDefault;
    uniDefault.flags = 0;
    uniDefault.add_uni("pos", glm::vec3(0.0f));
    uniDefault.add_uni("scale", glm::vec3(1.0f));
    uniDefault.add_uni("fOffset", glm::vec3(0.0f));
    uniDefault.add_uni("camPos", glm::mat4(1.0f));
    uniDefault.add_uni("rotation", glm::mat4(1.0f));
    uniDefault.add_uni("fRotation", glm::mat4(1.0f));
    uniDefault.add_uni("BoneMatrices", std::vector<glm::mat4>(20, glm::mat4(0.0f)));
    return uniDefault;
}

Uniforms light_uniforms(){
	Uniforms lightDefault;
    lightDefault.flags = 1;
    lightDefault.add_uni("pos", glm::vec3(0.0f));
    lightDefault.add_uni("scale", glm::vec3(1.0f));
    lightDefault.add_uni("lightColor", glm::vec4(1.0f));
    lightDefault.add_uni("camPos", glm::mat4(1.0f));
    return lightDefault;
}

Uniforms hitbox_uniforms(){
    Uniforms hitboxDefault;
    hitboxDefault.add_uni("pos", glm::vec3(0.0f));
    hitboxDefault.add_uni("camPos", glm::mat4(1.0f));
    return hitboxDefault;
}

// Mob* inputPath(){
//     std::string str;
//     std::cout << "Input file: " << std::endl;
//     std::getline(std::cin, str);
//     str = "Models/" + str;
//     std::cout << "Loading: " << str << std::endl;
//     return new Mob(importer(str.data()));
// }

Shader* g_hitboxShader;

int main(void) {
    Init();
    Scene scene;
    int defaultShader = scene.loadShader("Shaders/default.vert", "Shaders/default.frag", default_uniforms());
    int lightShader = scene.loadShader("Shaders/light.vert", "Shaders/light.frag", light_uniforms());
    int hitboxShader = scene.loadShader("Shaders/hitbox.vert", "Shaders/hitbox.frag", hitbox_uniforms());
    g_hitboxShader = &scene.shader(hitboxShader);
    
    LoadingParameters params;
    params.locateBones = {
        "ArmBot.L",
        "ArmBot.R",
        "ArmTop.L",
        "ArmTop.R",
        "Palm.L",
        "Palm.R",
    };

    scene.camera().updateProjection();
    scene.loadObject(PLAYER, "Models/player.fbx", params);
    scene.player().setWeapon(new Sword(importer("Models/sword.fbx"), &scene));
    int lightID = scene.loadObject(LIGHT, "Models/light.fbx");
    scene.light(lightID).addTarget(scene.shader(defaultShader));
    int floorID = scene.loadObject(STATIC, "Models/floor.fbx");
    int wallID = scene.loadObject(STATIC, "Models/wall.fbx");
    int mobID = scene.loadObject(MOB, "Models/enemy.fbx");
    int mobID2 = scene.loadObject(MOB, "Models/enemy.fbx");
    int mobID3 = scene.loadObject(MOB, "Models/enemy.fbx");
    int mobID4 = scene.loadObject(MOB, "Models/enemy.fbx");
    for (auto i = 0; i < scene.nObjects(); ++i)
        scene.object(i).setShader(defaultShader);
    scene.player().setShader(defaultShader);
    scene.light(lightID).setShader(lightShader);

    scene.player().setName("Player");
    scene.object(mobID).setName("Mob");
    scene.object(wallID).setPosition(5.0f, 0.0f, 5.0f);
    scene.object(wallID).setName("Wall");
    scene.object(mobID).setPosition(5.0f, 0.0f, 5.0f);
    scene.object(mobID).setCollide(true);
        scene.object(mobID2).setPosition(-5.0f, 0.0f, -5.0f);
        scene.object(mobID2).setCollide(true);
            scene.object(mobID3).setPosition(-5.0f, 0.0f, 5.0f);
            scene.object(mobID3).setCollide(true);
                scene.object(mobID4).setPosition(5.0f, 0.0f, -5.0f);
                scene.object(mobID4).setCollide(true);
    scene.object(wallID).setCollide(true);
    scene.object(wallID).setWeight(1.0f);
    scene.player().setCollide(true);

    int barID = scene.loadObject(DETAIL, "Models/bar.fbx");
    
    std::cout << "Lights: " << scene.nLights() << std::endl;
    std::cout << "Objects: " << scene.nObjects() << std::endl;
    std::cout << "Shader: " << scene.nShaders() << std::endl;

    while (!glfwWindowShouldClose(settings.window())) {
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.animate();
		// scene.light(0).animate(scene.shader(lightShader));
		// scene.player().animate(scene.shader(defaultShader));
		// scene.object(mobID).animate(scene.shader(defaultShader));
        // scene.object(floorID).animate(scene.shader(defaultShader));
        // std::cout << "Collision:\n";
        // std::cout << player.checkCollision(mob) << std::endl;
        // if (glfwGetKey(settings.window(), GLFW_KEY_1) == GLFW_PRESS){
        //     delete mob;
        //     mob = inputPath();
        // }
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
