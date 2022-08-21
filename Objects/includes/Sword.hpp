#pragma once

#include "Weapon.hpp"

class Scene;

class Sword : public Weapon
{		//
	public:
		Sword(Model model, Scene* scene)
            : Weapon(&model, scene, 10, 10, 10) {}

        ~Sword() {}

		void animate(const Shader& shader, Uniforms uni = Uniforms()){
            draw(shader, uni);
		}

};