#include "Scene.hpp"
#include "Importer.hpp"
#include "Quadtree.hpp"

Scene::Scene() {}

void Scene::checkRemovals(){
    for (auto i = 0; i < _spawners.size(); ++i)
        _spawners[i]->checkRemovals(_removals);
    for (auto i = 0; i < _removals.size(); ++i){
        auto it = _objects.find(_removals[i]);
        delete it->second;
        _objects.erase(it);
    }
    _removals.clear();
}

void Scene::collisions(){
    std::list<Object*> lst;
    lst.push_back(_player);
    _player->recalculateHitbox();
    for (auto it = _objects.begin(); it != _objects.end(); ++it){
        if (it->second->collide() == false)
            continue;
        lst.push_back(it->second);
        it->second->recalculateHitbox();
    }
    BoundingBox2D box(glm::vec2(-50.0f, -50.0f), glm::vec2(50.0f, 50.0f));
    Quadtree tree(box, lst, this);
    tree.build();
    tree.checkCollisions();
}

void Scene::animate(){
    _currentTime = glfwGetTime();
    for (auto i = 0; i < _spawners.size(); ++i)
        _spawners[i]->loop();
    _player->loop();
    for (auto it = _objects.begin(); it != _objects.end(); ++it)
        it->second->loop();
    collisions();
    _player->update();
    for (auto it = _objects.begin(); it != _objects.end(); ++it)
        it->second->update();
    checkRemovals();
}

int Scene::loadShader(const char* vert, const char* frag, const char* geo){
    _shaders.push_back(Shader(vert, frag, geo));
    return _shaders.size() - 1;
}

int Scene::loadModel(const char* path){
    int ID = 0;
    if (_models.size() != 0)
        ID = _models.rbegin()->first + 1;
    _models.insert(std::make_pair(ID, std::shared_ptr<Model>(new Model(importer(path), ID))));
    return ID;
}

int Scene::loadInstance(object_type type, int modelID){
    switch(type){
        case PLAYER:
            return (loadPlayerInstance(modelID));
        case LIGHT:
            return (loadLightInstance(modelID));
        case STATIC:
            return (loadStaticInstance(modelID));
        case MOB:
            return (loadMobInstance(modelID));
        default:
            assert(0);
    }
}

int Scene::loadPlayerInstance(int modelID){
    auto it = _models.find(modelID);
    assert(it != _models.end());
    assert(!_player);
    _player = new Player(it->second, this);
    return -1;
}

int Scene::loadLightInstance(int modelID){
    auto it = _models.find(modelID);
    assert(it != _models.end());
    int ID = 0;
    if (_objects.size() != 0)
        ID = _objects.rbegin()->first + 1;
    _objects.insert(std::make_pair(ID, new Light(it->second, this, ID)));
    return ID;
}

int Scene::loadStaticInstance(int modelID){
    auto it = _models.find(modelID);
    assert(it != _models.end());
    int ID = 0;
    if (_objects.size() != 0)
        ID = _objects.rbegin()->first + 1;
    _objects.insert(std::make_pair(ID, new Object(it->second, this, ID)));
    return ID;
}

int Scene::loadMobInstance(int modelID){
    auto it = _models.find(modelID);
    assert(it != _models.end());
    int ID = 0;
    if (_objects.size() != 0)
        ID = (_objects.rbegin()->first) + 1;
    auto ret = _objects.insert(std::make_pair(ID, new Mob(it->second, this, ID)));
    return ID;
}

int Scene::addSpawner(Spawner* spawner){
    assert(spawner != nullptr);
    int ID = 0;
    if (_spawners.size() != 0)
        ID = _spawners.rbegin()->first + 1;
    _spawners.insert(std::make_pair(ID, spawner));
    return ID;
}

int Scene::addObject(Object* object){
    assert(object != nullptr);
    int ID = 0;
    if (_objects.size() != 0)
        ID = _objects.rbegin()->first + 1;
    _objects.insert(std::make_pair(ID, object));
    return ID;
}

int Scene::getID() const{
    if (_objects.size() == 0)
        return 0;
    return _objects.rbegin()->first + 1;
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

const std::shared_ptr<Model>& Scene::model(int ID) const{
    auto it = _models.find(ID);
    assert(it != _models.end());
    // if (it == _models.end())
    //     return nullptr;
    return it->second;
}

Spawner* Scene::spawner(int ID) {
    auto it = _spawners.find(ID);
    if (it == _spawners.end())
        return nullptr;
    return it->second;
}

Shader* Scene::shader(int ID) {
    assert(ID < _shaders.size() && ID >= 0);
    return &_shaders[ID];
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

const Spawner* Scene::spawner(int ID) const {
    auto it = _spawners.find(ID);
    if (it == _spawners.end())
        return nullptr;
    return it->second;
}

const Shader* Scene::shader(int ID) const {
    assert(ID < _shaders.size() && ID >= 0);
    return &_shaders[ID];
}

// const Model* Scene::detail(int ID) const {
//     auto it = _details.find(ID);
//     if (it == _details.end())
//         return nullptr;
//     return it->second;
// }

float& Scene::time() {
    return _currentTime;
}

float& Scene::gravity() {
    return _gravity;
}

float Scene::time() const {
    return _currentTime;
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
