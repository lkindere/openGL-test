#include "Hitbox.hpp"
#include "settings.hpp"

extern Settings settings;
extern Shader* g_hitboxShader;

Hitbox::Hitbox() {}

bool Hitbox::checkCollision(const Hitbox& target) const {
    glm::vec3 min = _position + _min;
    glm::vec3 max = _position + _max;
    glm::vec3 min2 = target._position + target._min;
    glm::vec3 max2 = target._position + target._max;
    if (!(min.x <= max2.x && max.x >= min2.x))
        return false;
    if (!(min.y <= max2.y && max.y >= min2.y))
        return false;
    if (!(min.z <= max2.z && max.z >= min2.z))
        return false;
    return true;
}

// void Hitbox::updateHitbox(const glm::mat4& transformation){
//     // _transformation = transformation;
// }

void Hitbox::init(HitboxData& data){
    _min = std::move(data.min);
    _max = std::move(data.max);
    // std::cout << "Min:\n";
    // settings.printvec(_min);
    // std::cout << "Max:\n";
    // settings.printvec(_max);
    // std::cout << std::endl;
}

void Hitbox::setPosition(const glm::vec3& position){
    _position = position;
}

void Hitbox::setPosition(float x, float y, float z){
    _position.x = x; _position.y = y; _position.z = z;
}

void Hitbox::draw(const Shader& shader, Uniforms uniforms) const{
    std::vector<glm::vec3> vertices = {
        glm::vec3(_min.x, _min.y, _min.z),
        glm::vec3(_min.x, _max.y, _min.z),
        glm::vec3(_min.x, _min.y, _max.z),
        glm::vec3(_min.x, _max.y, _max.z),

        glm::vec3(_max.x, _min.y, _min.z),
        glm::vec3(_max.x, _max.y, _min.z),
        glm::vec3(_max.x, _min.y, _max.z),
        glm::vec3(_max.x, _max.y, _max.z),
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
    g_hitboxShader->update(uniforms);

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
