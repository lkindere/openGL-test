#pragma once

#include "Object.hpp"
#include "Sword.hpp"

#define ATTACK_ANIMATION 0
class Player : public Object
{
	public:
		Player(Model model);
        
		void input();

		void setWeapon(Weapon* wep);

        void animate(Shader& shader);

    private:
        void postTransformHands();

        void weaponTransformation(Uniforms& uni);

	private:
		Weapon* _weapon = nullptr;

		short _health = 10;
		short _energy = 10;

        float _speed = 0.1;
		float _walk = 0.1;
		float _run = 0.2;
		float _jump = 0.5;

	private:
		glm::vec3 _collision = glm::vec3(0.0f); //Don't really need floats for this
};
