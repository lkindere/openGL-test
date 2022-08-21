#include "Scene.hpp"
#include "Importer.hpp"

Scene::Scene() {}


void Scene::animate(){
    for (auto i = 0; i < _lights.size(); ++i)
        _lights[i]->animate(_shaders[_lights[i]->shader()]);
    _player->animate(_shaders[_player->shader()]);
    for (auto i = 0; i < _objects.size(); ++i)
        _objects[i]->animate(_shaders[_objects[i]->shader()]);
}

int Scene::loadShader(const char* vert, const char* frag, const Uniforms& uniforms){
    _shaders.push_back(Shader(vert, frag, uniforms));
    return _shaders.size() - 1;
}

//Loads an object and returns object ID
int Scene::loadObject(object_types type, const char* path, const LoadingParameters& params){
    switch(type){
        case PLAYER:
            assert(!_player);
            _player = new Player(importer(path, params), this);
            return -1;
        case LIGHT:
            _lights.push_back(new Light(importer(path, params), this));
            return _lights.size() - 1;
        case STATIC:
            _objects.push_back(new Object(importer(path, params), this));
            return _objects.size() - 1;
        case MOB:
            _objects.push_back(new Mob(importer(path, params), this));
            return _objects.size() - 1;
        default:
            assert(0);
    }
}

Camera& Scene::camera(){
    return _camera;
}

Player& Scene::player(){
    assert(_player);
    return *_player;
}

Light& Scene::light(unsigned int ID){
    assert(ID < _lights.size());
    return *_lights[ID];
}

Object& Scene::object(unsigned int ID){
    assert(ID < _objects.size());
    return *_objects[ID];
}

Shader& Scene::shader(unsigned int ID) {
    std::cout << "assert\n";
    assert(ID < _shaders.size());
    std::cout << "wat\n";
    return _shaders[ID];
}

const Camera& Scene::camera() const {
    return _camera;
}

const Player& Scene::player() const {
    assert(_player);
    return *_player;
}

const Light& Scene::light(unsigned int ID) const {
    assert(ID < _lights.size());
    return *_lights[ID];
}

const Object& Scene::object(unsigned int ID) const {
    assert(ID < _objects.size());
    return *_objects[ID];
}

const Shader& Scene::shader(unsigned int ID) const {
    std::cout << "assert\n";
    assert(ID < _shaders.size());
    std::cout << "wat\n";
    return _shaders[ID];
}

float& Scene::gravity() {
    return _gravity;
}

float Scene::gravity() const {
    return _gravity;
}

unsigned int Scene::nLights() const {
    return _lights.size();
}

unsigned int Scene::nObjects() const {
    return _objects.size();
}

unsigned int Scene::nShaders() const {
    return _shaders.size();
}