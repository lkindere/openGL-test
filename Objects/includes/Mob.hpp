#pragma once

#include "Model.hpp"

#include "Object.hpp"
#include "Weapon.hpp"
#include "Camera.hpp"
#include "settings.hpp"

extern Settings settings;
extern Camera camera;

class Mob : public Object
{
	public:
		Mob(Model model);
        
    public:
        void animate(const Shader& shader);

    private:
        void facePlayer();

	private:
		Weapon* weapon = nullptr;

    private:
		short _health = 10;
		short _energy = 10;
        float _speed = 0.1;
};
