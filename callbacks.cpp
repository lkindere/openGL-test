#include "callbacks.hpp"
#include "settings.hpp"

extern Settings settings;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
#if DEBUG > 1
    std::cout << "KEYPRESS:\n";
    std::cout << "Key:      " << key << '\n';
    std::cout << "Scancode: " << scancode << '\n';
    std::cout << "Action:   " << action << '\n';
    std::cout << "Mods:     " << mods << '\n'
              << std::endl;
#endif
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void error_callback(int error_code, const char* description) {
    std::cout << "ERROR\n";
    std::cout << "Error code:  " << error_code << 'n';
    std::cout << "Description: " << description << 'n' << std::endl;
}

void GLdebug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                      GLsizei length, const GLchar* message, const void* userParam) {
    std::cout << "Error of type: " << type << '\n';
    std::cout << message << '\n'
              << std::endl;
}