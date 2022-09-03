#include "Mob.hpp"
#include "Scene.hpp"

glm::vec3 noY(const glm::vec3& vec){
    return glm::vec3(vec.x, 0.0f, vec.z);
}

// Mob::Mob(MeshData data, Scene* scene, int ID)
//     : Object(&data, scene, ID) {
//     _info.setType(MOB);
//     _info.setCollide(true);
//     setPosition(1.0f, 0.0f, 1.0f);
// }

Mob::Mob(const std::shared_ptr<Model>& modelptr, Scene* scene, int ID)
    : Object(modelptr, scene, ID) {
    _info.setType(MOB);
    _info.setCollide(true);
    setPosition(1.0f, 0.0f, 1.0f);
}

bool Mob::checkDeath(){
    if (_health > 0)
        return 0;
    setCollide(false);
    _flags |= deformOn;
    float time = glfwGetTime();
    if (lastTick != 0)
        currentTick += (time - lastTick);
    lastTick = time;
    _uniforms.add_uni("uTime", currentTick);
    draw();
    if (currentTick > 1.0f)
        _scene->removeObject(ID());
    return 1;
}

void Mob::loop(){
    if (checkDeath())
        return ;
    facePlayer();
    applyGravity();
}

void Mob::update(){
    animLoop();
    move();
    InstanceData data;
    glm::mat3 rot = _rotation;
    data.position = _position;
    data.rotL1 = rot[0];
    data.rotL2 = rot[1];
    data.rotL3 = rot[2];
    _model->buffer(data);
    // draw();
    drawHealth();
}

void Mob::drawHealth(){
    float barSize = (float)_health / _maxHealth;
    _uniforms.add_uni("pos", _position + glm::vec3(0.0f, 2.5f, 0.0f));
    _uniforms.add_uni("scale", glm::vec3((float)_health / _maxHealth, 1.0f, (float)_health / _maxHealth));
    // _scene->detail(0)->draw(*_scene->shader(_shader), _uniforms);
}

void Mob::damage(short dmg){
    _health -= dmg;
}

void Mob::facePlayer(){
    static glm::quat lastQuat;

    _direction = glm::normalize(noY(_scene->player()->position()) - noY(_position));
    float angle = glm::orientedAngle(glm::vec3(0.0f, 0.0f, 1.0f), _direction, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::quat newQuat = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f));
    lastQuat = glm::slerp(lastQuat, newQuat, _speed);

    _rotation = toMat4(lastQuat);
    _velocity += _direction * _speed;
}

Mob::~Mob() {
    std::cout << "Mob is rip\n";
}