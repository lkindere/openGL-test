#include "callbacks.hpp"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	#ifdef DEBUG
		std::cout << "KEYPRESS:\n";
		std::cout << "Key:      " << key << '\n';
		std::cout << "Scancode: " << scancode << '\n';
		std::cout << "Action:   " << action << '\n';
		std::cout << "Mods:     " << mods << '\n' << std::endl;
	#endif
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void error_callback(int error_code, const char* description)
{
	std::cout << "ERROR\n";
	std::cout << "Error code:  " << error_code << 'n';
	std::cout << "Description: " << description << 'n' << std::endl;
}
