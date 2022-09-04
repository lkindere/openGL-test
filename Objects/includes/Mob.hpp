#pragma once

#include "Object.hpp"

class Scene;

class Mob : public Object
{
	public:
        Mob(const std::shared_ptr<Model>& modelptr, Scene* scene, int ID);
        
        ~Mob();
        
        void loop();
        void update();
        void damage(short dmg);

    private:
        void drawHealth();
        void facePlayer();
        bool checkDeath();

    private:
        float lastTick = 0;
        float currentTick = 0;

    private:
        const short _maxHealth = 10;
        
		short _health = 10;
		short _energy = 10;
        float _speed = 0.05;
};
