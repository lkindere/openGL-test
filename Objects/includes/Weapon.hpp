#pragma once

#include "Object.hpp"

class Scene;

class Weapon : public Object
{
	public:
		Weapon(MeshData* data, Scene* scene, short damage, float range, float speed)
            : Object(data, scene), _damage(damage), _range(range), _speed(speed) {}
		virtual ~Weapon() {}

        virtual void animate(const Shader& shader, Uniforms uni = Uniforms()) = 0;

        short damage() const { return _damage; }
        short range() const { return _range; }
        short speed() const { return _speed; }

    protected:
        const short _damage;
        const float _range;
        const float _speed;
};
