#pragma once

#include <fstream>
#include <sstream>

#include "glad/gl.h"

class Shaders {
   public:
    Shaders(const char* vertPath, const char* fragPath);
    void activate();
    void destroy();
    GLuint getID();

   private:
    GLuint ID;
};
