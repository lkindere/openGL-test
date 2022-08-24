#include "Scene.hpp"
#include "Importer.hpp"

Scene::Scene() {}


void Scene::checkRemovals(){
    for (auto i = 0; i < _removals.size(); ++i){
        auto it = _objects.find(_removals[i]);
        delete it->second;
        _objects.erase(it);
    }
    _removals.clear();
}

void Scene::animate(){
    _player->animate();
    for (auto it = _objects.begin(); it != _objects.end(); ++it)
        it->second->animate();
    checkRemovals();
}

int Scene::loadShader(const char* vert, const char* frag, const char* geo){
    _shaders.push_back(Shader(vert, frag, geo));
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
            return (loadLight(path, params));
        case STATIC:
            return (loadStatic(path, params));
        case MOB:
            return (loadMob(path, params));
        case DETAIL:
            return (loadDetail(path, params));
        default:
            assert(0);
    }
}

int Scene::loadInstance(object_types type, int modelID){
    switch(type){
        case LIGHT:
            return (loadLightInstance(modelID));
        case STATIC:
            return (loadStaticInstance(modelID));
        case MOB:
            return (loadMobInstance(modelID));
        // case DETAIL:
        //     return (loadDetail(path, params));
        default:
            assert(0);
    }
}

int Scene::loadLight(const char* path, const LoadingParameters& params){
    int ID = 0;
    if (_objects.size() != 0)
        ID = _objects.rbegin()->first + 1;
    _objects.insert(std::make_pair(ID, new Light(importer(path, params), this, ID)));
    return ID;
}

int Scene::loadStatic(const char* path, const LoadingParameters& params){
    int ID = 0;
    if (_objects.size() != 0)
        ID = _objects.rbegin()->first + 1;
    _objects.insert(std::make_pair(ID, new Object(importer(path, params), this, ID)));
    return ID;
}

int Scene::loadMob(const char* path, const LoadingParameters& params){
    int ID = 0;
    if (_objects.size() != 0)
        ID = _objects.rbegin()->first + 1;
    _objects.insert(std::make_pair(ID, new Mob(importer(path, params), this, ID)));
    return ID;
}

int Scene::loadDetail(const char* path, const LoadingParameters& params){
    int ID = 0;
    if (_details.size() != 0)
        ID = _details.rbegin()->first + 1;
    _details.insert(std::make_pair(ID, new Model(importer(path, params))));
    return ID;
}

int Scene::loadLightInstance(int modelID){
    auto it = _objects.find(modelID);
    assert(it != _objects.end());
    int ID = _objects.rbegin()->first + 1;
    _objects.insert(std::make_pair(ID, new Light(it->second->model(), this, ID)));
    return ID;
}

int Scene::loadStaticInstance(int modelID){
    auto it = _objects.find(modelID);
    assert(it != _objects.end());
    int ID = _objects.rbegin()->first + 1;
    _objects.insert(std::make_pair(ID, new Object(it->second->model(), this, ID)));
    return ID;
}

int Scene::loadMobInstance(int modelID){
    auto it = _objects.find(modelID);
    assert(it != _objects.end());
    int ID = _objects.rbegin()->first + 1;
    _objects.insert(std::make_pair(ID, new Mob(it->second->model(), this, ID)));
    return ID;
}

void Scene::removeObject(int ID){
    _removals.push_back(ID);
}

Camera& Scene::camera(){
    return _camera;
}

Player* Scene::player(){
    assert(_player);
    return _player;
}

Object* Scene::object(int ID){
    auto it = _objects.find(ID);
    if (it == _objects.end())
        return nullptr;
    return it->second;
}

Shader* Scene::shader(int ID) {
    assert(ID < _shaders.size() && ID >= 0);
    return &_shaders[ID];
}

Model* Scene::detail(int ID) {
    auto it = _details.find(ID);
    if (it == _details.end())
        return nullptr;
    return it->second;
}

const Camera& Scene::camera() const {
    return _camera;
}

const Player* Scene::player() const {
    assert(_player);
    return _player;
}

const Object* Scene::object(int ID) const {
    auto it = _objects.find(ID);
    if (it == _objects.end())
        return nullptr;
    return it->second;
}

const Shader* Scene::shader(int ID) const {
    assert(ID < _shaders.size() && ID >= 0);
    return &_shaders[ID];
}

const Model* Scene::detail(int ID) const {
    auto it = _details.find(ID);
    if (it == _details.end())
        return nullptr;
    return it->second;
}

float& Scene::gravity() {
    return _gravity;
}

float Scene::gravity() const {
    return _gravity;
}

unsigned int Scene::nObjects() const {
    return _objects.size();
}

unsigned int Scene::nShaders() const {
    return _shaders.size();
}

std::map<int, Object*>::iterator        Scene::oBegin(){
    return _objects.begin();
}

std::map<int, Object*>::const_iterator  Scene::oBegin() const{
    return _objects.begin();
}

std::map<int, Object*>::iterator        Scene::oEnd(){
    return _objects.end();
}

std::map<int, Object*>::const_iterator  Scene::oEnd() const{
    return _objects.end();
}
