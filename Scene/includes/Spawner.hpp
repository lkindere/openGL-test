#pragma once

#include "Structs.hpp"

class Model;
class Scene;

class PositionGenerator
{
    public:
        PositionGenerator();
        PositionGenerator(const glm::vec3& position, const glm::vec3& min, const glm::vec3& max);
        
        glm::vec3 generatePosition();

        void setPosition(const glm::vec3& position);
        void setRange(const glm::vec3& min, const glm::vec3& max);

        const glm::vec3& position() const;
        const glm::vec3& rangeMin() const;
        const glm::vec3& rangeMax() const;

    protected:
        glm::vec3 _position = glm::vec3(0.0f);
        glm::vec3 _rangeMin = glm::vec3(0.0f);
        glm::vec3 _rangeMax = glm::vec3(0.0f);
};

class Spawner : public PositionGenerator
{
    public:
        Spawner(std::shared_ptr<Model> modelptr, Scene* scene);
        
        void loop();
        void spawn();
        void checkRemovals(const std::vector<int>& removals);

    private:
        Scene*                  _scene;
        float                   _interval = 1.0f;
        PositionGenerator       _generator;
        std::shared_ptr<Model>  _model;
        std::vector<int>        _ID;

};
