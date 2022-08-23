#pragma once

#include "Object.hpp"
#include "Sword.hpp"

#define ATTACK_ANIMATION 0

class Scene;

class Player : public Object
{
	public:
		Player(MeshData data, Scene* scene);
 
		void setWeapon(Weapon* wep);

        void animate();

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
        bool  _attacking = false;

	private:
		glm::vec3 _collision = glm::vec3(0.0f); //Don't really need floats for this
};
