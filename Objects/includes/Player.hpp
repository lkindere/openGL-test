#pragma once

// #include <cmath>

#include "Sword.hpp"
#include "Camera.hpp"

#include "Model.hpp"

#include "settings.hpp"

#include <iostream>

extern Settings settings;
extern Camera camera;

#define ATTACK_ANIMATION 0

class Player
{
	public:
		Player(Model model)
			: _model(std::move(model)) {}
        
		void input() {
            if (glfwGetMouseButton(settings.window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                _model.setAnim(ATTACK_ANIMATION);
                _model.setLoop(false);
            }
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
                camera.setPosition(new_position + glm::vec3(0.0f, 2.0f, 0.0f) + (direction * glm::vec3(0.1f, 0.0f, 0.1f)));
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
			delete weapon;
			weapon = wep;
		}

        void draw(Shader& shader){
            if (camera.mode() == first_person){
                rotation = glm::rotate(glm::mat4(1.0f), glm::radians(camera.yaw()), glm::vec3(0.0f, 1.0f, 0.0f));
                postTransformHands();
            }
            Uniforms uni;
            uni.add_uni("pos", position);
            uni.add_uni("rotation", rotation);
            uni.add_uni("camPos", camera.matrix());
            _model.updateHitbox(glm::inverse(rotation));
            _model.draw(shader, uni);
			if (weapon){
                weaponTransformation(uni);
				weapon->draw(shader, uni);
            }
		}

    private:
        void postTransformHands(){
            glm::mat4 limbUpL = glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3((camera.pitch() + 30.0f) / 100, 0.0f, 0.0f)));
            glm::mat4 limbUpR = glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(-(camera.pitch() + 30.0f) / 100, 0.0f, 0.0f)));
            _model.findNode("ArmBot.L")->postTransform(limbUpL);
            _model.findNode("ArmBot.R")->postTransform(limbUpR);

            glm::mat4 limbRotL = glm::rotate(glm::mat4(1.0f), glm::radians(-(camera.pitch() + 30.0f) / 20), glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 limbRotR = glm::rotate(glm::mat4(1.0f), glm::radians((camera.pitch() + 30.0f) / 20), glm::vec3(0.0f, 0.0f, 1.0f));
            _model.findNode("ArmTop.L")->postTransform(limbRotL);
            _model.findNode("ArmTop.R")->postTransform(limbRotR);
        }

        void weaponTransformation(Uniforms& uni){
            const NodeData* limb = _model.findNode("Palm.L");
            const glm::mat4& transformation = _model.getBoneMatrix(limb->ID());
            glm::mat4 rot = {
                transformation[0][0], transformation[0][1], transformation[0][2], 0.0f,
                transformation[1][0], transformation[1][1], transformation[1][2], 0.0f,
                transformation[2][0], transformation[2][1], transformation[2][2], 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            };
            rot = glm::rotate(rot, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            glm::vec3 limbpos = position + glm::vec3(transformation * glm::vec4(limb->position(), 1.0f) * rotation);
            uni.add_uni("pos", limbpos);
            uni.add_uni("fRotation", rot);
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
