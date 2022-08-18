#include "Object.hpp"

Object::Object(Model model)
    : _model(std::move(model)) {}

Object::Object(Model* model)
    : _model(std::move(*model)) {}

Object::~Object() {}

//Returns uniform used in previous draw call
//Alternative would be to store last used uni on class and use a getter
Uniforms Object::draw(const Shader& shader, Uniforms uni){
    uni.add_uni("pos", _position);
    uni.add_uni("rotation", _rotation);
    uni.add_uni("camPos", camera.matrix());
    _model.draw(shader, uni);
    return uni;
}

const glm::vec3&    Object::front() const { return _front; }
const glm::vec3&    Object::position() const { return _position; }
const glm::vec3&    Object::direction() const { return _direction; }
const glm::mat4&    Object::rotation() const { return _rotation; }
const Model&        Object::model() const { return _model; }

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
