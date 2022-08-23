#include "Mob.hpp"
#include "Scene.hpp"
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/quaternion.hpp>

glm::vec3 noY(const glm::vec3& vec){
    return glm::vec3(vec.x, 0.0f, vec.z);
}

Mob::Mob(MeshData data, Scene* scene)
    : Object(&data, scene) {
    _model.setAnim(0);
    _model.setLoop(true);
    setPosition(1.0f, 0.0f, 1.0f);
}

void Mob::animate(const Shader& shader, Uniforms uni){
    facePlayer();
    _velocity += _direction * _speed;
    move();
    uni.add_uni("flags", _flags);
    std::cout << "uTime: " << (float)glfwGetTime() << std::endl;
    uni.add_uni("uTime", (float)glfwGetTime());
    std::cout << "Uni uTime: " << uni.f1.find("uTime")->second << std::endl;
    uni = draw(shader, uni);
    float barSize = (float)_health / _maxHealth;
    uni.add_uni("scale", glm::vec3(barSize, 1.0f, barSize));
    uni.add_uni("pos", _position + glm::vec3(0.0f, 2.5f, 0.0f));
    _scene->detail(0).draw(shader, uni);
}

void Mob::damage(short dmg){
    _health -= dmg;
    //Temp
    if (_health < _maxHealth)
        _flags = _flags | 2;
}

void Mob::facePlayer(){
    static glm::quat lastQuat;

    _direction = glm::normalize(noY(_scene->player().position()) - noY(_position));
    float angle = glm::orientedAngle(glm::vec3(0.0f, 0.0f, 1.0f), _direction, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::quat newQuat = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f));
    lastQuat = glm::slerp(lastQuat, newQuat, _speed);

    _rotation = toMat4(lastQuat);
}

Mob::~Mob() {}