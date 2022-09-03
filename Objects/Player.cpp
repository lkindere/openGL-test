#include "Player.hpp"
#include "Scene.hpp"

// Player::Player(MeshData data, Scene* scene, int ID)
//     : Object(&data, scene, ID) {
//     _info.setType(PLAYER);
// }

Player::Player(const std::shared_ptr<Model>& modelptr, Scene* scene, int ID)
    : Object(modelptr, scene, ID) {
    _info.setType(PLAYER);
}

void Player::input() {
    if (_scene->camera().mode() == detached){
        _scene->camera().input();
        return ;
    }
    if (glfwGetMouseButton(settings.window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        if (_mdata.anim != ATTACK_ANIMATION){
            animate(ATTACK_ANIMATION, false);
            attack();
        }
    }
    if (_scene->camera().mode() != detached)
        _direction.y = 0;
    if (glfwGetKey(settings.window(), GLFW_KEY_W) == GLFW_PRESS)
        _velocity += _speed * _direction;
    if (glfwGetKey(settings.window(), GLFW_KEY_S) == GLFW_PRESS)
        _velocity += _speed * -_direction;
    if (glfwGetKey(settings.window(), GLFW_KEY_A) == GLFW_PRESS)
        _velocity += _speed * glm::normalize(glm::cross(-_direction, _up));
    if (glfwGetKey(settings.window(), GLFW_KEY_D) == GLFW_PRESS)
        _velocity += _speed * glm::normalize(glm::cross(_direction, _up));
    if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        _speed = _run;
    if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        _speed = _walk;
    if (glfwGetKey(settings.window(), GLFW_KEY_SPACE) == GLFW_PRESS && _position.y == 0.0f)
        _velocity += _jump * _up;
    _direction = _scene->camera().mouseDirection();
}

void Player::setWeapon(Weapon* wep){
    delete _weapon;
    _weapon = wep;
    _attackInterval *= _weapon->speed();
}

void Player::attack(){
    if (!_weapon)
        return;
    for (auto it = _scene->oBegin(); it != _scene->oEnd(); ++it){
        if (it->second->collide() == false)
            continue ;
        //Fix this
        if (glm::distance(it->second->position(), _position) < _weapon->range())
            it->second->damage(_weapon->damage());
    }
}

void Player::loop(){
    input();
    applyGravity();
}

void Player::update(){
    move();
    if (_scene->camera().mode() == first_person){
        _scene->camera().setPosition(_position + glm::vec3(0.0f, 2.0f, 0.0f) + (_direction * glm::vec3(0.1f, 0.0f, 0.1f)));
        _rotation = glm::inverse(glm::rotate(glm::mat4(1.0f), glm::radians(_scene->camera().yaw()), glm::vec3(0.0f, 1.0f, 0.0f)));
        postTransformHands();
    }
    else if (_scene->camera().mode() == third_person){
        _scene->camera().setPosition(_position + glm::vec3(0.0f, 3.0f, 0.0f) + (-_direction * glm::vec3(2.0f, 0.0f, 2.0f)));
        _rotation = glm::inverse(glm::rotate(glm::mat4(1.0f), glm::radians(_scene->camera().yaw()), glm::vec3(0.0f, 1.0f, 0.0f)));
        postTransformHands();
    }
    draw();
    if (_weapon){
        weaponTransformation();
        _weapon->loop();
        _weapon->draw();
    }
    animLoop();
}

void Player::postTransformHands(){
    glm::mat4 limbUpL = glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3((_scene->camera().pitch() + 30.0f) / 100, 0.0f, 0.0f)));
    glm::mat4 limbUpR = glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(-(_scene->camera().pitch() + 30.0f) / 100, 0.0f, 0.0f)));
    _mdata.postTransforms["ArmBot.L"] = limbUpL;
    _mdata.postTransforms["ArmBot.R"] = limbUpR;

    glm::mat4 limbRotL = glm::rotate(glm::mat4(1.0f), glm::radians(-(_scene->camera().pitch() + 30.0f) / 20), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 limbRotR = glm::rotate(glm::mat4(1.0f), glm::radians((_scene->camera().pitch() + 30.0f) / 20), glm::vec3(0.0f, 0.0f, 1.0f));
    _mdata.postTransforms["ArmTop.L"] = limbRotL;
    _mdata.postTransforms["ArmTop.R"] = limbRotR;
}

void Player::weaponTransformation(){
    const NodeData* limb = _model->findNode("Palm.L");
    const glm::mat4& transformation = _uniforms.mat4.find("BoneMatrices")->second[limb->ID()];
    glm::mat4 rot = {
        transformation[0][0], transformation[0][1], transformation[0][2], 0.0f,
        transformation[1][0], transformation[1][1], transformation[1][2], 0.0f,
        transformation[2][0], transformation[2][1], transformation[2][2], 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    rot = glm::rotate(rot, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    rot = glm::rotate(rot, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 limbpos = _position + glm::vec3(transformation * glm::vec4(limb->position(), 1.0f) * glm::inverse(_rotation));
    _weapon->setPosition(limbpos);
    _weapon->setDirection(_direction);
    _weapon->setRotation(_rotation * rot);
}
