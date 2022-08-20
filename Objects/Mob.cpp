#include "Mob.hpp"
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/quaternion.hpp>

glm::vec3 noY(const glm::vec3& vec){
    return glm::vec3(vec.x, 0.0f, vec.z);
}

Mob::Mob(Model model)
    : Object(&model) {
    _model.setAnim(0);
    _model.setLoop(true);
}

void Mob::animate(const Shader& shader){
    facePlayer();
    _velocity += _direction * _speed;
    move();
    setHitboxPosition(_position);
    draw(shader);
}

void Mob::facePlayer(){
    static glm::quat lastQuat;

    _direction = glm::normalize(noY(camera.position()) - noY(_position));
    float angle = glm::orientedAngle(glm::vec3(0.0f, 0.0f, 1.0f), _direction, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::quat newQuat = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f));
    lastQuat = glm::slerp(lastQuat, newQuat, _speed);

    _rotation = toMat4(lastQuat);
}