#pragma once

#include "Weapon.hpp"

class Sword : public Weapon
{		//
	public:
		Sword(Model model)
            : Weapon(&model, 10, 10, 10) {}

		void animate(const Shader& shader, Uniforms uni = Uniforms()){
            draw(shader, uni);
		}

};