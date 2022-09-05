#pragma once

#include "main.hpp"

#include "Object.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include "Terrain.hpp"
#include "Player.hpp"
#include "Mob.hpp"
#include "Light.hpp"

#include "Spawner.hpp"

class Scene
{
    public:
        Scene();

        void animate();
        void collisions();
        int loadShader(const char* vert, const char* frag, const char* geo = nullptr);
        int loadModel(const char* path, int shader);
        int loadTerrain(const char* path, int shader);
        int loadInstance(object_type type, int modelID);
        void animate() const;
    
    public:
        //Spawner
        int addSpawner(Spawner* spawner);
        int getID() const;
        int addObject(Object* object);

    private:
        void checkRemovals();
        int loadPlayerInstance(int modelID);
        int loadLightInstance(int modelID);
        int loadStaticInstance(int modelID);
        int loadMobInstance(int modelID);
        // int Scene::loadDetailInstance(int modelID);
    
    public:
        void removeObject(int ID);

        Camera& camera();
        Player* player();
        Object* object(int ID);
        // Model* detail(int ID);
        Spawner* spawner(int ID);
        Shader* shader(int ID);
        const Camera& camera() const;
        const Player* player() const;
        const Object* object(int ID) const;
        const Spawner* spawner(int ID) const;
        const Shader* shader(int ID) const;
        const std::shared_ptr<Model>& model(int ID) const;

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
        float _gravity = 0.1f;

    private:
        Camera                                  _camera;
        Player*                                 _player = nullptr;
        std::map<int, std::shared_ptr<Model> >  _models;
        std::map<int, Spawner*>                 _spawners;
        std::map<int, Object*>                  _objects;
        std::vector<Terrain>                    _terrains;
        std::vector<Shader>                     _shaders;
        std::vector<int>                        _removals;
};