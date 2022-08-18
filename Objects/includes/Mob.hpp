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
        void move(Uniforms& uni);

	private:
		Weapon* weapon = nullptr;

    private:
		short health = 10;
		short energy = 10;
        float speed = 0.1;
};
