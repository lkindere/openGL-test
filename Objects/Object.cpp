#include "Object.hpp"

Object::Object(Model model)
    : _model(std::move(model)) {}

Object::Object(Model* model)
    : _model(std::move(*model)) {}

Object::~Object() {}

void Object::move(){
    _velocity = glm::mix(_velocity, glm::vec3(0.0f, _velocity.y, 0.0f), _weight);
    if (_position.y > 0.0f)
        _velocity.y -= settings.gravity() * _weight;
    _position += _velocity;
    if (_position.y < 0.0f){
        _position.y = 0.0f;
        _velocity.y = 0.0f;   
    }
}

//Returns uniform used in previous draw call
//Alternative would be to store last used uni on class and use a getter
Uniforms Object::draw(const Shader& shader, Uniforms uni){
    uni.add_uni("pos", _position);
    uni.add_uni("rotation", _rotation);
    uni.add_uni("camPos", camera.matrix());
    _model.draw(shader, uni);
    return uni;
}

void Object::collisionPhysics(Object& target){
    _position += (_velocity - target._velocity);
    target._position += (target._velocity - _velocity);
}

bool Object::checkCollision(Object& target){
    if (hitbox().checkCollision(target.hitbox()) == false)
        return false;
    collisionPhysics(target);
    return true;
}

const glm::vec3&    Object::front() const { return _front; }
const glm::vec3&    Object::position() const { return _position; }
const glm::vec3&    Object::direction() const { return _direction; }
const glm::mat4&    Object::rotation() const { return _rotation; }
const Model&        Object::model() const { return _model; }
const Hitbox&       Object::hitbox() const { return _model.hitbox(); }

void    Object::setFront(const glm::vec3& vec) {
    _front = vec;
}

void    Object::setFront(float x, float y, float z) {
    _front.x = x; _front.y = y; _front.z = z;
}

void    Object::setPosition(const glm::vec3& vec) {
    _position = vec;
}

void    Object::setPosition(float x, float y, float z) {
    _position.x = x; _position.y = y; _position.z = z;
}

void    Object::setDirection(const glm::vec3& vec) {
    _direction = vec;
}

void    Object::setDirection(float x, float y, float z) {
    _direction.x = x; _direction.y = y; _direction.z = z;
}

void Object::setRotation(const glm::mat4& mat){
    _rotation = mat;
}

void Object::setHitboxPosition(const glm::vec3& vec){
    _model.setHitboxPosition(vec);
}

void Object::setHitboxPosition(float x, float y, float z){
    _model.setHitboxPosition(glm::vec3(x, y, z));
}

void Object::setVelocity(const glm::vec3& vec){
    _velocity = vec;
}

void Object::setVelocity(float x, float y, float z){
    _velocity.x = x; _velocity.y = y; _velocity.z = z;
}

void Object::setWeight(float x){
    _weight = x;
}