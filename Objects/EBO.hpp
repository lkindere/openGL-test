#pragma once

#include <glad/gl.h>
#include <vector>

class EBO {
   public:
    EBO(std::vector<GLuint>& indices);
    void bind();
    void unbind();
    void destroy();

   private:
    GLuint ID;
};
