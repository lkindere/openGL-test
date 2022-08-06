#pragma once

#include "Model.hpp"

#include "settings.hpp"

extern Settings settings;
extern Camera camera;

class Mob
{
	public:
		Mob(const Model& model)
			: _model(model) {}
		// void setWeapon(Weapon* wep){
		// 	delete weapon;
		// 	weapon = wep;
		// }

        void draw(const Shader& shader){
			Uniforms uni;
			uni.vec3 = {
				std::make_pair("pos", position),
				std::make_pair("scale", glm::vec3(0.01f)),
			};
            uni.mat4 = {
                std::make_pair("camPos", camera.matrix())
            };
			_model.draw(shader, uni);
			move();
		}
		void move(){
			direction = camera.position() - position;
			direction.y = 0.0f;
			position += direction * (speed / 10);
		}

	private:
		Mob& operator=(const Mob& p);
		Mob(const Mob& p);

	private:
		Weapon* weapon = nullptr;
		short health = 10;
		short energy = 10;
        float speed = 0.1;
    
    private:
        glm::vec3 position = glm::vec3(5.0f, 0.0f, 5.0f);
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);

        Model _model;
};
