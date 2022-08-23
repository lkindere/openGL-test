#pragma once

#include "Object.hpp"

class Scene;

class Mob : public Object
{
	public:
		Mob(MeshData data, Scene* scene);
        ~Mob();
        
        void animate();
        void damage(short dmg);

    private:
        void facePlayer();

    private:
        const short _maxHealth = 10;
        
		short _health = 10;
		short _energy = 10;
        float _speed = 0.1;
};
