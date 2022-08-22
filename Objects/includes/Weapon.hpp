#pragma once

#include "Object.hpp"

class Scene;

class Weapon : public Object
{
	public:
		Weapon(MeshData* data, Scene* scene, short damage, short range, short speed)
            : Object(data, scene), _damage(damage), _range(range), _speed(speed) {}
		virtual ~Weapon() {}

        virtual void animate(const Shader& shader, Uniforms uni = Uniforms()) = 0;

    protected:
        const short _damage;
        const short _range;
        const short _speed;
};
