#pragma once

#include "Object.hpp"
#include "Sword.hpp"

#define ATTACK_ANIMATION 0

class Scene;

class Player : public Object
{
	public:
		Player(MeshData data, Scene* scene, int ID = -1);
        Player(const std::shared_ptr<Model>& modelptr, Scene* scene, int ID = -1);
 
		void setWeapon(Weapon* wep);

        void loop();

    private:
		void input();
        void attack();
        void postTransformHands();

        void weaponTransformation();

	private:
		Weapon* _weapon = nullptr;

		short _health = 10;
		short _energy = 10;

        float _speed = 0.1;
		float _walk = 0.1;
		float _run = 0.2;
		float _jump = 0.5;

    private:
        float _attackInterval = 1.0f;
};
