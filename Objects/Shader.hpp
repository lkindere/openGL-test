#pragma once

#include <fstream>
#include <sstream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Shader {
   public:
    Shader(const char* vertPath, const char* fragPath);
    void bind();
	void unbind();
    void destroy();
    GLuint getID();

   private:
    GLuint ID;
};
