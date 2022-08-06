#pragma once

#include "Sword.hpp"
#include "Camera.hpp"

#include "Model.hpp"

#include "settings.hpp"

#include <iostream>

extern Settings settings;
extern Camera camera;

class Player
{
	public:
		Player(const Model& model)
			: _model(model) {}
		void input() {
			// direction.y = 0;
			if (glfwGetKey(settings.window(), GLFW_KEY_W) == GLFW_PRESS)
				position += speed * direction;
			if (glfwGetKey(settings.window(), GLFW_KEY_S) == GLFW_PRESS)
				position -= speed * direction;
			if (glfwGetKey(settings.window(), GLFW_KEY_A) == GLFW_PRESS)
				position -= speed * glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(settings.window(), GLFW_KEY_D) == GLFW_PRESS)
				position += speed * glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				speed = run;
			if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
				speed = walk;
			if (glfwGetKey(settings.window(), GLFW_KEY_SPACE) == GLFW_PRESS && collision.y){
				collision.y = 0;
				velocity.y = settings.gravity() * jump;
			}
            camera.setPosition(position);
			direction = camera.mouseDirection();
			physics();
		}
        
		void physics(){
			if (!collision.y){
				velocity.y -= settings.gravity();
				position.y += velocity.y;
				if (position.y <= 2.0){
					position.y = 2.0;
					velocity.y = 0;
					collision.y = 1;
				}
			}
		}

		void setWeapon(Weapon* wep){
			delete weapon;
			weapon = wep;
		}

        void draw(Shader& shader){
			if (weapon)
				weapon->draw(shader, position, direction);
		}

	private:
		Player& operator=(const Player& p);
		Player(const Player& p);

	private:
		Weapon* weapon = nullptr;
		short health = 10;
		short energy = 10;
        float speed = 0.1;
		float walk = 0.1;
		float run = 0.2;
		short jump = 30;
    
    private:
        glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);

		Model	_model;

	private:
		glm::vec3 velocity = glm::vec3(0.0f);
		glm::vec3 collision = glm::vec3(0.0f); //Don't really need floats for this
};
