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
            glm::vec3 new_position = camera.position();
            if (camera.mode() == first_person){
			    direction.y = 0;
                new_position = position;
            }
			if (glfwGetKey(settings.window(), GLFW_KEY_W) == GLFW_PRESS)
				new_position += speed * direction;
			if (glfwGetKey(settings.window(), GLFW_KEY_S) == GLFW_PRESS)
				new_position -= speed * direction;
			if (glfwGetKey(settings.window(), GLFW_KEY_A) == GLFW_PRESS)
				new_position -= speed * glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(settings.window(), GLFW_KEY_D) == GLFW_PRESS)
				new_position += speed * glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				speed = run;
			if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
				speed = walk;
			if (glfwGetKey(settings.window(), GLFW_KEY_SPACE) == GLFW_PRESS && collision.y){
				collision.y = 0;
				velocity.y = settings.gravity() * jump;
			}
			direction = camera.mouseDirection();
            camera.setPosition(new_position);
            if (camera.mode() == first_person){
                camera.setPosition(new_position + glm::vec3(0.0f, 4.0f, 0.0f) + (direction * glm::vec3(1.0f, 0.0f, 1.0f)));
                position = new_position;
                physics();
            }
		}
        
		void physics(){
			if (!collision.y){
				velocity.y -= settings.gravity();
				position.y += velocity.y;
				if (position.y < 0.0){
					position.y = 0.0;
					velocity.y = 0;
					collision.y = 1;
				}
			}
		}

		void setWeapon(Weapon* wep){
            std::cout << "SEG\n";
			delete weapon;
			weapon = wep;
		}

        void draw(Shader& shader){
            if (camera.mode() == first_person)
                rotation = glm::rotate(glm::mat4(1.0f), glm::radians(camera.yaw()), glm::vec3(0.0f, 1.0f, 0.0f));
            Uniforms uni;
            uni.vec3 = {
                make_uni("pos", position),
                // make_uni("scale", glm::vec3(1.0f))
            };
            uni.mat4 = {
				make_uni("rotation", rotation),
                make_uni("camPos", camera.matrix())
			};
            _model.draw(shader, uni);
			if (weapon){
                const LimbData* limb = _model.getLimbData("Palm.L");
                if (limb == nullptr){
                    std::cout << "LIMB NOT FOUND\n";
                    exit(0);
                    return ;
                }
                const glm::mat4& transformation = _model.getBoneMatrix(limb->boneID);
                glm::vec3 limbpos = transformation * glm::vec4(limb->position, 1.0f) * rotation;
                limbpos += position;
				weapon->draw(shader, limbpos);
            }
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
        glm::mat4 rotation = glm::mat4(1.0f);
        glm::mat4 rightHand = glm::mat4(1.0f);

		Model	_model;

	private:
		glm::vec3 velocity = glm::vec3(0.0f);
		glm::vec3 collision = glm::vec3(0.0f); //Don't really need floats for this
};
