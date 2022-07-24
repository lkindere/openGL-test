#pragma once

#include <fstream>
#include <sstream>

#include <glad/gl.h>

class Shader {
   public:
    Shader(const char* vertPath, const char* fragPath);
    void activate();
    void destroy();
    GLuint getID();

   private:
    GLuint ID;
};
