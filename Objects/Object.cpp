#include "Object.hpp"
#include "Scene.hpp"

Object::Object(MeshData data, Scene* scene)
    : _hitbox(data.hitbox), _model(std::move(data)), _scene(scene){
    setHitboxPosition(_position);
}

Object::Object(MeshData* data, Scene* scene)
    : _hitbox(data->hitbox), _model(std::move(*data)), _scene(scene){
    setHitboxPosition(_position);
}

Object::~Object() {}

void Object::move(){
    if (_position.y > 0.0f)
        _velocity.y -= _scene->gravity() * _weight;
    setHitboxPosition(_position + _velocity, _rotation);
    checkCollision();
    _position += _velocity;
    if (_position.y < 0.0f){
        _position.y = 0.0f;
        _velocity.y = 0.0f;   
    }
    _velocity = glm::mix(_velocity, glm::vec3(0.0f, _velocity.y, 0.0f), _weight);
}

void Object::animate(const Shader& shader, Uniforms uni){
    draw(shader, uni);
}

void Object::damage(short dmg) { return; }

//Returns uniform used in previous draw call
//Alternative would be to store last used uni on class and use a getter
Uniforms Object::draw(const Shader& shader, Uniforms uni){
    uni.add_uni("pos", _position);
    uni.add_uni("rotation", _rotation);
    uni.add_uni("camPos", _scene->camera().matrix());
    _model.draw(shader, uni);
    _hitbox.draw(uni);
    return uni;
}

void Object::collisionPhysics(Object& target){
    if (glfwGetKey(settings.window(), GLFW_KEY_F) == GLFW_PRESS)
        return ;
    float dot = glm::dot(_velocity, target._position - _position);
    if (dot <= 0.0f)
        return ;
    _velocity = glm::mix(_velocity, glm::vec3(0.0f), target._weight);
    target._velocity = glm::mix(target._velocity, glm::vec3(0.0f), _weight);
    glm::vec3 temp = _velocity;
    target._velocity = glm::mix(target._velocity, temp, 0.5);
    if (!target.checkCollision())
        _velocity = glm::mix(_velocity, target._velocity, 0.5);
    else
        _velocity = glm::vec3(0.0f);
}

bool Object::checkCollision(){
    if (_collide == false)
        return false;
    bool collision = false;
    if (&_scene->player() != this){
        if (hitbox().checkCollision(_scene->player().hitbox()) == true){
            collisionPhysics(_scene->player());
            collision = true;
        }
    }
    for (auto i = 0; i < _scene->nObjects(); ++i){
        if (&_scene->object(i) == this || _scene->object(i).collide() == false)
            continue ;
        if (hitbox().checkCollision(_scene->object(i).hitbox()) == false)
            continue ;
        collisionPhysics(_scene->object(i));
        collision = true;
    }
    return collision;
}

const std::string&  Object::name() const { return _name; }
bool                Object::collide() const { return _collide; }
int                 Object::shader() const { return _shader; }
int                 Object::flags() const { return _flags; }
const glm::vec3&    Object::front() const { return _front; }
const glm::vec3&    Object::position() const { return _position; }
const glm::vec3&    Object::direction() const { return _direction; }
const glm::mat4&    Object::rotation() const { return _rotation; }
const Model&        Object::model() const { return _model; }
const Hitbox&       Object::hitbox() const { return _hitbox; }


void Object::setName(const std::string& name){
    _name = name;
}

void    Object::setCollide(bool b){
    _collide = b;
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
    setHitboxPosition(_position);
}

void    Object::setPosition(float x, float y, float z){
    _position.x = x; _position.y = y; _position.z = z;
    setHitboxPosition(x, y, z);
}

void    Object::setDirection(const glm::vec3& vec){
    _direction = vec;
}

void    Object::setDirection(float x, float y, float z){
    _direction.x = x; _direction.y = y; _direction.z = z;
}

void Object::setRotation(const glm::mat4& mat){
    _rotation = mat;
}

void Object::setHitboxPosition(const glm::vec3& vec, const glm::mat4& rotation){
    _hitbox.setPosition(vec, rotation);
}

void Object::setHitboxPosition(float x, float y, float z, const glm::mat4& rotation){
    _hitbox.setPosition(x, y, z, rotation);
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