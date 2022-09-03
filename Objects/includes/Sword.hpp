#pragma once

#include "Weapon.hpp"

class Scene;

class Sword : public Weapon
{		//
	public:
		// Sword(MeshData data , Scene* scene, int ID)
        //     : Weapon(&data, scene, ID, 5, 1.0, 1.0) {}

        Sword(const std::shared_ptr<Model>& modelptr, Scene* scene, int ID)
            : Weapon(modelptr, scene, ID, 5, 1.0, 1.0) {}

        ~Sword() {}

};