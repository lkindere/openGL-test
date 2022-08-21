#pragma once

#include "Object.hpp"

class Scene;

class Mob : public Object
{
	public:
		Mob(Model model, Scene* scene);
        
        void animate(const Shader& shader, Uniforms uni = Uniforms());

    private:
        void facePlayer();

    private:
		short _health = 10;
		short _energy = 10;
        float _speed = 0.1;
};
