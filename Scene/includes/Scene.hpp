#pragma once

#include "Structs.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

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
    DETAIL,
};

class Scene
{
    public:
        Scene();

        void animate();
        int loadShader(const char* vert, const char* frag, const Uniforms& uniforms);
        int loadObject(object_types type, const char* path, const LoadingParameters& params = LoadingParameters());
        void animate() const;
        
        Camera& camera();
        Player& player();
        Light&  light(unsigned int ID);
        Object& object(unsigned int ID);
        Model& detail(unsigned int ID);
        Shader& shader(unsigned int ID);
        const Camera& camera() const;
        const Player& player() const;
        const Light&  light(unsigned int ID) const;
        const Object& object(unsigned int ID) const;
        const Shader& shader(unsigned int ID) const;
        const Model& detail(unsigned int ID) const;

        float& gravity();
        float gravity() const;

    public:
        unsigned int nLights() const;
        unsigned int nObjects() const;
        unsigned int nShaders() const;

    private:
        float _gravity = 0.2f;

    private:
        Camera                  _camera;
        Player*                 _player = nullptr;
        std::vector<Light*>     _lights;
        std::vector<Object*>    _objects;
        std::vector<Model*>     _details;
        std::vector<Shader>     _shaders;
};