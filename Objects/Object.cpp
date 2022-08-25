#include "Object.hpp"
#include "Scene.hpp"

Object::Object(MeshData data, Scene* scene, int ID)
    : _model(std::shared_ptr<Model>(new Model(std::move(data)))),
        _scene(scene), _ID(ID) {}

Object::Object(MeshData* data, Scene* scene, int ID)
    : _model(std::shared_ptr<Model>(new Model(std::move(*data)))),
        _scene(scene), _ID(ID) {}

Object::Object(const std::shared_ptr<Model>& modelptr, Scene* scene, int ID)
    : _model(modelptr), _scene(scene), _ID(ID) {}

void Object::setDefaultUniforms(){
    _uniforms.flags = _flags;
    _uniforms.add_uni("pos", _position);
    _uniforms.add_uni("scale", _scale);
    _uniforms.add_uni("rotation", _rotation);
    _uniforms.add_uni("camPos", _scene->camera().matrix());
    _uniforms.add_uni("BoneMatrices", _model->generateMatrices(_mdata));
}

void Object::move(){
    if (_position.y > 0.0f)
        _velocity.y -= _scene->gravity() * _weight;
    checkCollision();
    _position += _velocity;
    if (_position.y < 0.0f){
        _position.y = 0.0f;
        _velocity.y = 0.0f;   
    }
    _velocity = glm::mix(_velocity, glm::vec3(0.0f, _velocity.y, 0.0f), _weight);
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
    animLoop();
    draw();
}

void Object::damage(short dmg) {}

void Object::draw(){
    setDefaultUniforms();
    _model->draw(*_scene->shader(_shader), _uniforms);
    hitbox().draw(_uniforms);
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
    if (_scene->player() != this){
        if (hitbox().checkCollision(*this, *_scene->player()) == true){
            collisionPhysics(*_scene->player());
            collision = true;
            if (collision){
                Mob* mob = dynamic_cast<Mob*>(this);
                if (mob != nullptr && !mob->animating())
                    mob->animate(0, false);
            }
        }
    }
    for (auto it = _scene->oBegin(); it != _scene->oEnd(); ++it){
        if (it->second->collide() == false || it->second == this)
            continue ;
        if (hitbox().checkCollision(*this, *it->second) == false)
            continue ;
        collisionPhysics(*it->second);
        collision = true;
    }
    return collision;
}

int                 Object::ID() const { return _ID; }
const std::string&  Object::name() const { return _name; }
bool                Object::collide() const { return _collide; }
bool                Object::animating() const { return _animating; }
int                 Object::shader() const { return _shader; }
int                 Object::flags() const { return _flags; }
const glm::vec3&    Object::front() const { return _front; }
const glm::vec3&    Object::position() const { return _position; }
const glm::vec3&    Object::direction() const { return _direction; }
const glm::vec3&    Object::velocity() const { return _velocity; }
const glm::vec3&    Object::scale() const { return _scale; }
const glm::mat4&    Object::rotation() const { return _rotation; }
const Hitbox&       Object::hitbox() const { return _model->hitbox(); }

const std::shared_ptr<Model>&   Object::model() const { return _model; }


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

void Object::setScale(const glm::vec3& vec) {
    _scale = vec;
}

void Object::setScale(float x, float y, float z) {
    _scale.x = x; _scale.y = y; _scale.z = z;
}

void Object::setRotation(const glm::mat4& mat){
    _rotation = mat;
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

Object::~Object() {}
