#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ArrayObject.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Weapon.hpp"

#include "settings.hpp"

extern Settings settings;
extern Camera camera;

#include <unistd.h>

class Sword : public Weapon
{		//
	public:
		Sword(Model model)
			: _model(std::move(model)) {}

		void draw(Shader& shader, const Uniforms& uni){
			_model.draw(shader, uni);
		}
        
	private:
		const short damage = 10;
		const short range = 10;
		const short speed = 10;
		Model _model;
};