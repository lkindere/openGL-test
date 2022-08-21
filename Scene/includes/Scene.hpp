#pragma once

#include "Structs.hpp"
#include "Object.hpp"
#include "Camera.hpp"

#include "Player.hpp"
#include "Mob.hpp"
#include "Light.hpp"

#include "debug.hpp"

enum object_types
{
    STATIC,
    LIGHT,
    PLAYER,
    MOB,
};

class Scene
{
    public:
        Scene();

        int loadObject(object_types type, const char* path, const LoadingParameters& params = LoadingParameters());
        
        Camera& camera();
        Player& player();
        Light&  light(int ID);
        Object& object(int ID);
        const Camera& camera() const;
        const Player& player() const;
        const Light&  light(int ID) const;
        const Object& object(int ID) const;

        float& gravity();
        float gravity() const;

    public:
        size_t nLights() const;
        size_t nObjects() const;

    private:
        float _gravity = 0.2f;

    private:
        Camera                  _camera;
        Player*                 _player = nullptr;
        std::vector<Light*>     _lights;
        std::vector<Object*>    _objects;
};