#pragma once

#include "Object.hpp"

class Scene;

class Weapon : public Object
{
	public:
		Weapon(MeshData* data, Scene* scene, int ID, short damage, float range, float speed)
            : Object(data, scene, ID), _damage(damage), _range(range), _speed(speed) {}
        //Looks ridiculous with stat initialization
        Weapon(const std::shared_ptr<Model>& modelptr, Scene* scene, int ID, short damage, float range, float speed)
            : Object(modelptr, scene, ID), _damage(damage), _range(range), _speed(speed) {}

		virtual ~Weapon() {}

        short damage() const { return _damage; }
        short range() const { return _range; }
        short speed() const { return _speed; }

    protected:
        const short _damage;
        const float _range;
        const float _speed;
};
