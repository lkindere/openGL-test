#include "Mob.hpp"
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/quaternion.hpp>

Mob::Mob(Model model) : _model(std::move(model)) {
    _model.setAnim(0);
    _model.setLoop(true);
}

void Mob::draw(const Shader& shader){
    Uniforms uni;
    uni.add_uni("pos", position);
    uni.add_uni("camPos", camera.matrix());
    move(uni);
    _model.draw(shader, uni);
}

glm::vec3 noY(const glm::vec3& vec){
    return glm::vec3(vec.x, 0.0f, vec.z);
}

void Mob::move(Uniforms& uni){
    glm::vec3 direction = glm::normalize(noY(camera.position()) - noY(position));
    float angle = glm::orientedAngle(glm::vec3(0.0f, 0.0f, 1.0f), direction, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotation = toMat4(glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f)));
    uni.add_uni("fRotation", rotation);
    position += direction * speed;
}
