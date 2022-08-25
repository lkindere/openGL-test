#pragma once

#include "Structs.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include "Player.hpp"
#include "Mob.hpp"
#include "Light.hpp"

#include "Spawner.hpp"

#include "debug.hpp"

enum object_types
{
    STATIC,
    LIGHT,
    PLAYER,
    MOB,
    DETAIL,
};

enum shader_flags
{
    hasTexture = 1,
    deformOn = 2,
};

class Scene
{
    public:
        Scene();

        void animate();
        int loadShader(const char* vert, const char* frag, const char* geo = nullptr);
        int loadObject(object_types type, const char* path);
        int loadInstance(object_types type, int modelID);
        void animate() const;
    
    public:
        //Spawner
        int addSpawner(Spawner* spawner);
        int getID() const;
        int addObject(Object* object);

    private:
        void checkRemovals();
        int loadLight(const char* path);
        int loadStatic(const char* path);
        int loadMob(const char* path);
        int loadDetail(const char* path);
        int loadLightInstance(int modelID);
        int loadStaticInstance(int modelID);
        int loadMobInstance(int modelID);
        // int Scene::loadDetailInstance(int modelID);
    
    public:
        void removeObject(int ID);

        Camera& camera();
        Player* player();
        Object* object(int ID);
        Model* detail(int ID);
        Spawner* spawner(int ID);
        Shader* shader(int ID);
        const Camera& camera() const;
        const Player* player() const;
        const Object* object(int ID) const;
        const Model* detail(int ID) const;
        const Spawner* spawner(int ID) const;
        const Shader* shader(int ID) const;

        float& time();
        float& gravity();
        float time() const;
        float gravity() const;


    public:
        unsigned int nObjects() const;
        unsigned int nShaders() const;

    public:
        std::map<int, Object*>::iterator        oBegin();
        std::map<int, Object*>::const_iterator  oBegin() const;
        std::map<int, Object*>::iterator        oEnd();
        std::map<int, Object*>::const_iterator  oEnd() const;


    private:
        float _currentTime = 0.0f;

    private:
        float _gravity = 0.2f;

    private:
        Camera                  _camera;
        Player*                 _player = nullptr;
        std::map<int, Object*>  _objects;
        std::map<int, Model*>   _details;
        std::map<int, Spawner*> _spawners;
        std::vector<Shader>     _shaders;
        std::vector<int>        _removals;
};