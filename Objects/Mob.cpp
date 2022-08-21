#include "Mob.hpp"
#include "Scene.hpp"
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/quaternion.hpp>

glm::vec3 noY(const glm::vec3& vec){
    return glm::vec3(vec.x, 0.0f, vec.z);
}

Mob::Mob(Model model, Scene* scene)
    : Object(&model, scene) {
    _model.setAnim(0);
    _model.setLoop(true);
    setPosition(0.1f, 0.0f, 0.1f);
}

void Mob::animate(const Shader& shader, Uniforms uni){
    facePlayer();
    _velocity += _direction * _speed;
    move();
    draw(shader, uni);
}

void Mob::facePlayer(){
    static glm::quat lastQuat;

    _direction = glm::normalize(noY(_scene->player().position()) - noY(_position));
    float angle = glm::orientedAngle(glm::vec3(0.0f, 0.0f, 1.0f), _direction, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::quat newQuat = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f));
    lastQuat = glm::slerp(lastQuat, newQuat, _speed);

    _rotation = toMat4(lastQuat);
}
