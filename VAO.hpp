#pragma once

#include <glad/gl.h>

#include "VBO.hpp"

class VAO {
   public:
    VAO();
    void linkAttri(VBO vbo, GLuint layout, GLuint components, GLenum type,
                   GLsizeiptr stride, void* offset);
    void bind();
    void unbind();
    void destroy();

   private:
    GLuint ID;
};