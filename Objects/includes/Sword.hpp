#pragma once

#include "Weapon.hpp"

class Scene;

class Sword : public Weapon
{		//
	public:
        Sword(const std::shared_ptr<Model>& modelptr, Scene* scene, int ID)
            : Weapon(modelptr, scene, ID, 5, 1.0, 1.0) {}

        ~Sword() {}

};