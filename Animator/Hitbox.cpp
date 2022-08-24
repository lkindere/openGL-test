#include "Hitbox.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Object.hpp"

extern Shader* g_hitboxShader;

Hitbox::Hitbox(const HitboxData& data)
    : _min(data.min), _max(data.max) {}

bool Hitbox::checkCollision(const Object& obj, const Object& target) const {
    glm::vec3 min = obj.position() + obj.velocity() + _min;
    glm::vec3 max = obj.position() + obj.velocity() + _max;
    glm::vec3 min2 = target.position() + target.velocity() + target.hitbox()._min;
    glm::vec3 max2 = target.position() + target.velocity() + target.hitbox()._max;
    if (!(min.x <= max2.x && max.x >= min2.x))
        return false;
    if (!(min.y <= max2.y && max.y >= min2.y))
        return false;
    if (!(min.z <= max2.z && max.z >= min2.z))
        return false;
    return true;
}

void Hitbox::draw(const Uniforms& uni) const{
    glm::vec3 min = _rotation * _min;
    glm::vec3 max = _rotation * _max;
    std::vector<glm::vec3> vertices = {
        glm::vec3(min.x, min.y, min.z),
        glm::vec3(min.x, max.y, min.z),
        glm::vec3(min.x, min.y, max.z),
        glm::vec3(min.x, max.y, max.z),

        glm::vec3(max.x, min.y, min.z),
        glm::vec3(max.x, max.y, min.z),
        glm::vec3(max.x, min.y, max.z),
        glm::vec3(max.x, max.y, max.z),
    };
    std::vector<GLuint> indices = {
        0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7,
        1, 0, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7,
        2, 0, 2, 1, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7,
        3, 0, 3, 1, 3, 2, 3, 4, 3, 5, 3, 6, 3, 7,

        4, 5, 4, 6, 4, 7, 4, 0, 4, 1, 4, 2, 4, 3,
        5, 4, 5, 6, 5, 7, 5, 0, 5, 1, 5, 2, 5, 3,
        6, 4, 6, 5, 6, 7, 6, 0, 6, 1, 6, 2, 6, 3,
        7, 4, 7, 5, 7, 6, 7, 0, 7, 1, 7, 2, 7, 3,
    };
    g_hitboxShader->bind();
    g_hitboxShader->update(uni);

    GLuint temp;
    glGenVertexArrays(1, &temp);
	glBindVertexArray(temp);

    GLuint VerticeBuffer;
	glGenBuffers(1, &VerticeBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VerticeBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STREAM_DRAW);

	GLuint IndiceBuffer;
	glGenBuffers(1, &IndiceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndiceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STREAM_DRAW);

    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, (void*)0);

    glDeleteBuffers(1, &VerticeBuffer);
    glDeleteBuffers(1, &IndiceBuffer);
    glDeleteVertexArrays(1, &temp);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    g_hitboxShader->unbind();
}
