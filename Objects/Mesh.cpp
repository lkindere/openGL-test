#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
    : vertices(vertices), indices(indices) {
    VAO.bind();
    VBO vbo(vertices);
    EBO ebo(indices);
    // Position
    VAO.linkAttri(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
    // Normal
    VAO.linkAttri(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (3 * sizeof(float)));
    // Color
    VAO.linkAttri(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (6 * sizeof(float)));
    VAO.unbind();
    vbo.unbind();
    ebo.unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera) {
    shader.activate();
    VAO.bind();
    camera.Matrix(45.0f, 0.1f, 100.0f, shader,
                  "camMatrix");  // Skipped something here
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
