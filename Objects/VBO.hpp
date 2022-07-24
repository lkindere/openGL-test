#pragma once

#include <glad/gl.h>

class VBO {
   public:
    VBO(GLfloat* vertices, GLsizeiptr size);
    void bind();
    void unbind();
    void destroy();

   private:
    GLuint ID;
};
