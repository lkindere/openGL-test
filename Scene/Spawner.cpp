#include "Spawner.hpp"
#include "Scene.hpp"

Spawner::Spawner(std::shared_ptr<Model> modelptr, Scene* scene)
    : _model(modelptr), _scene(scene) {}

void Spawner::checkRemovals(const std::vector<int>& removals){
    for (auto i = 0; i < removals.size(); ++i){
        auto it = std::find(_ID.begin(), _ID.end(), removals[i]);
        if (it != _ID.end())
            _ID.erase(it);
    }
}

void Spawner::spawn(){
    int ID = _scene->getID();
    Mob* mob = new Mob(_model, _scene, ID);
    mob->setPosition(generatePosition());
    _scene->addObject(mob);
    _ID.push_back(ID);
}

void Spawner::loop(){
    static float lastTick;
    static float currentTick;
    float time = glfwGetTime();
    if (lastTick != 0)
        currentTick += (time - lastTick);
    if (currentTick >= _interval){
        currentTick = 0.0f;
        spawn();
    }
    lastTick = time;
}

PositionGenerator::PositionGenerator() {
    srand(time(NULL));
}

PositionGenerator::PositionGenerator(const glm::vec3& position,
    const glm::vec3& min, const glm::vec3& max)
    : _position(position), _rangeMin(min), _rangeMax(max) {
    srand(time(NULL));
}

glm::vec3 PositionGenerator::generatePosition(){
    float i1 = (float)rand() / RAND_MAX;
    float i2 = (float)rand() / RAND_MAX;
    float i3 = (float)rand() / RAND_MAX;
    float x = glm::mix(_rangeMin.x, _rangeMax.x, i1);
    float y = glm::mix(_rangeMin.y, _rangeMax.y, i2);
    float z = glm::mix(_rangeMin.z, _rangeMax.z, i3);
    return _position + glm::vec3(x, y, z);
}

void PositionGenerator::setPosition(const glm::vec3& position){
    _position = position;
}

void PositionGenerator::setRange(const glm::vec3& min, const glm::vec3& max){
    _rangeMin = min;
    _rangeMax = max;
}

const glm::vec3& PositionGenerator::position() const{
    return _position;
}

const glm::vec3& PositionGenerator::rangeMin() const{
    return _rangeMin;
}

const glm::vec3& PositionGenerator::rangeMax() const{
    return _rangeMax;
}