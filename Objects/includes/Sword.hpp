#pragma once

#include "Weapon.hpp"

class Scene;

class Sword : public Weapon
{		//
	public:
		Sword(MeshData data , Scene* scene)
            : Weapon(&data, scene, 2, 1.0, 1.0) {}

        ~Sword() {}

};