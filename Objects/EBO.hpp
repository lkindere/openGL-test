#pragma once

#include <glad/gl.h>

class EBO {
   public:
    EBO(GLuint* indices, GLsizeiptr size);
    void bind();
    void unbind();
    void destroy();

   private:
    GLuint ID;
};
