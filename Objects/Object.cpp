#include "Object.hpp"
#include "Scene.hpp"

Object::Object(const std::shared_ptr<Model>& modelptr, Scene* scene, int ID)
    : _model(modelptr), _scene(scene), _info(ID) {}

void Object::recalculateHitbox(){
    _hitbox.recalculate(_model->hitboxBase(), glm::inverse(_rotation));
}

void Object::applyGravity(){
    _velocity.y -= _scene->gravity() * _weight;
}

void Object::move(){
    _position += _velocity;
    _velocity = glm::mix(_velocity, glm::vec3(0.0f, _velocity.y, 0.0f), _weight);
    // _scene->terrain(0)->height(_position);
    if (_position.y < 10.0f){
        _velocity.y = 0.0f;
        _position.y = 10.0f;
    }
}

void Object::animate(int ID, bool loop){
    _mdata.time = 0;
    _mdata.anim = ID;
    _mdata.loop = loop;
    _animating = true;
    _aDuration = _model->duration(ID);
    _aStart = _scene->time();
}

void Object::animLoop(){
    if (!_animating)
        return ;
    float elapsed = _scene->time() - _aStart;
    _mdata.time = elapsed;
    if (elapsed >= _aDuration){
        _mdata.time = 0;
        _mdata.anim = -1;
        _mdata.loop = false;
        _animating = false;
        _aStart = 0;
        _aDuration = 0;
    }
}

void Object::loop(){
    applyGravity();
    _newRotation = false;
}

void Object::update(){
    animLoop();
    move();
    InstanceData data;
    data.position = _position;
    data.rotL1 = _rotation[0];
    data.rotL2 = _rotation[1];
    data.rotL3 = _rotation[2];
    _model->buffer(data, _mdata);
}

void Object::damage(short dmg) {}

void Object::collisionPhysics(Object& target, CollisionData& data){
    if (glfwGetKey(settings.window(), GLFW_KEY_F) == GLFW_PRESS)
        return ;
    target._velocity -= glm::mix(data.overlap * -data.normal, glm::vec3(0.0f), target._weight);
    _velocity -= glm::mix(data.overlap * data.normal, glm::vec3(0.0f), 1.00 - target._weight);
}

void Object::checkCollision(Object& target){
    if (&target == this || type() == STATIC)
        return;
    CollisionData collision = hitbox().checkCollision(*this, target);
    if (collision.overlap != 0)
        collisionPhysics(target, collision);
}

int                 Object::ID() const { return _info.ID(); }
const std::string&  Object::name() const { return _info.name(); }
object_type         Object::type() const { return _info.type(); }
bool                Object::collide() const { return _info.collide(); }
bool                Object::isInstanced() const { return _model.use_count() > 1; }
bool                Object::isStatic() const { return _info.type() == STATIC; }
bool                Object::animating() const { return _animating; }
int                 Object::shader() const { return _shader; }
int                 Object::flags() const { return _flags; }
const glm::vec3&    Object::front() const { return _front; }
const glm::vec3&    Object::direction() const { return _direction; }
const glm::vec3&    Object::position() const { return _position; }
const glm::vec3&    Object::velocity() const { return _velocity; }
glm::vec3           Object::finalpos() const { return _position + _velocity; }
const glm::vec3&    Object::scale() const { return _scale; }
const glm::mat4&    Object::rotation() const { return _rotation; }
Hitbox&             Object::hitbox() { return _hitbox; }
const Hitbox&       Object::hitbox() const { return _hitbox; }

glm::vec3           Object::HBmin() const { return _hitbox.min() + finalpos(); }
glm::vec3           Object::HBmax() const { return _hitbox.max() + finalpos(); }

const std::shared_ptr<Model>&   Object::model() const { return _model; }


void    Object::setName(const std::string& name){
    _info.setName(name);
}

void    Object::setType(object_type type){
    _info.setType(type);
}

void    Object::setCollide(bool b){
    _info.setCollide(b);
}

void    Object::setShader(int ID){
    _shader = ID;
}

void    Object::setFlags(int flags){
    _flags = flags;
}

void    Object::setFront(const glm::vec3& vec){
    _front = vec;
}

void    Object::setFront(float x, float y, float z){
    _front.x = x; _front.y = y; _front.z = z;
}

void    Object::setPosition(const glm::vec3& vec){
    _position = vec;
}

void    Object::setPosition(float x, float y, float z){
    _position.x = x; _position.y = y; _position.z = z;
}

void    Object::setDirection(const glm::vec3& vec){
    _direction = vec;
}

void    Object::setDirection(float x, float y, float z){
    _direction.x = x; _direction.y = y; _direction.z = z;
}

void    Object::setScale(const glm::vec3& vec) {
    _scale = vec;
}

void    Object::setScale(float x, float y, float z) {
    _scale.x = x; _scale.y = y; _scale.z = z;
}

void    Object::setRotation(const glm::mat4& mat){
    _rotation = mat;
    _newRotation = true;
}

void    Object::setVelocity(const glm::vec3& vec){
    _velocity = vec;
}

void    Object::setVelocity(float x, float y, float z){
    _velocity.x = x; _velocity.y = y; _velocity.z = z;
}

void    Object::setWeight(float x){
    _weight = x;
}

Object::~Object() {}
