#include "Mob.hpp"
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/quaternion.hpp>

glm::vec3 noY(const glm::vec3& vec){
    return glm::vec3(vec.x, 0.0f, vec.z);
}

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


void Mob::move(Uniforms& uni){
    static glm::quat lastQuat;

    glm::vec3 direction = glm::normalize(noY(camera.position()) - noY(position));
    float angle = glm::orientedAngle(glm::vec3(0.0f, 0.0f, 1.0f), direction, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::quat newQuat = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f));

    lastQuat = glm::slerp(lastQuat, newQuat, 0.005f);

    glm::mat4 rotation = toMat4(lastQuat);

    _model.updateHitbox(rotation);
    uni.add_uni("fRotation", rotation);

    position += direction * (speed / 10);
}
