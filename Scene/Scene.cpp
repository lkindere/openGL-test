#include "Scene.hpp"
#include "Importer.hpp"

Scene::Scene() {}

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

Light& Scene::light(int ID){
    assert(ID < _lights.size());
    return *_lights[ID];
}

Object& Scene::object(int ID){
    assert(ID < _objects.size());
    return *_objects[ID];
}

const Camera& Scene::camera() const {
    return _camera;
}

const Player& Scene::player() const {
    assert(_player);
    return *_player;
}

const Light& Scene::light(int ID) const {
    assert(ID < _lights.size());
    return *_lights[ID];
}

const Object& Scene::object(int ID) const {
    assert(ID < _objects.size());
    return *_objects[ID];
}

float& Scene::gravity() {
    return _gravity;
}

float Scene::gravity() const {
    return _gravity;
}

size_t Scene::nLights() const {
    return _lights.size();
}
size_t Scene::nObjects() const {
    return _objects.size();
}