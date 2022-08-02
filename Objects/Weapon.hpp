#pragma once

#include "settings.hpp"
#include "Weapon.hpp"
#include "ArrayObject.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern Settings settings;

class Weapon
{
	public:
		Weapon() {}
		virtual ~Weapon() {}
		// virtual void attack()
		virtual void draw(Shader& shader, const glm::vec3& pos, const glm::vec3& dir) = 0;
};