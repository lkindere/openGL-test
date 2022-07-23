#pragma once

#define GLFW_INCLUDE_NONE 
#include <GLFW/glfw3.h>

#include <iostream>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void error_callback(int error_code, const char* description);