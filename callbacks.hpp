#pragma once

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE 
#include <GLFW/glfw3.h>

#include <iostream>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

void error_callback(int error_code, const char* description);
void GLdebug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                      GLsizei length, const GLchar* message, const void* userParam);