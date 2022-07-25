#include "VAO.hpp"

VAO::VAO() { glGenVertexArrays(1, &ID); }
void VAO::linkAttri(VBO& vbo, GLuint layout, GLuint components, GLenum type,
                    GLsizeiptr stride, GLsizeiptr offset) {
    vbo.bind();
    glVertexAttribPointer(layout, components, type, GL_FALSE, stride, (void *)offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}
void VAO::bind() { glBindVertexArray(ID); }
void VAO::unbind() { glBindVertexArray(0); }
void VAO::destroy() { glDeleteVertexArrays(1, &ID); }