#pragma once

#include "Object.hpp"
#include "Sword.hpp"

#define ATTACK_ANIMATION 0

class Player : public Object
{
	public:
		Player(Model model)
			: Object(std::move(&model)) {}
        
		void input() {
            if (glfwGetMouseButton(settings.window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                _model.setAnim(ATTACK_ANIMATION);
                _model.setLoop(false);
            }
            glm::vec3 newPos = camera.position();
            if (camera.mode() == first_person){
			    _direction.y = 0;
                newPos = _position;
            }
			if (glfwGetKey(settings.window(), GLFW_KEY_W) == GLFW_PRESS)
				newPos += _speed * _direction;
			if (glfwGetKey(settings.window(), GLFW_KEY_S) == GLFW_PRESS)
				newPos -= _speed * _direction;
			if (glfwGetKey(settings.window(), GLFW_KEY_A) == GLFW_PRESS)
				newPos -= _speed * glm::normalize(glm::cross(_direction, glm::vec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(settings.window(), GLFW_KEY_D) == GLFW_PRESS)
				newPos += _speed * glm::normalize(glm::cross(_direction, glm::vec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				_speed = _run;
			if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
				_speed = _walk;
			if (glfwGetKey(settings.window(), GLFW_KEY_SPACE) == GLFW_PRESS && _collision.y){
				_collision.y = 0;
				_velocity.y = settings.gravity() * _jump;
			}
			_direction = camera.mouseDirection();
            camera.setPosition(newPos);
            if (camera.mode() == first_person){
                camera.setPosition(newPos + glm::vec3(0.0f, 2.0f, 0.0f) + (_direction * glm::vec3(0.1f, 0.0f, 0.1f)));
                _position = newPos;
                physics();
            }
		}
        
		void physics(){
			if (!_collision.y){
				_velocity.y -= settings.gravity();
				_position.y += _velocity.y;
				if (_position.y < 0.0){
					_position.y = 0.0;
					_velocity.y = 0;
					_collision.y = 1;
				}
			}
		}

		void setWeapon(Weapon* wep){
			delete _weapon;
			_weapon = wep;
		}

        void animate(Shader& shader){
            if (camera.mode() == first_person){
                _rotation = glm::inverse(glm::rotate(glm::mat4(1.0f), glm::radians(camera.yaw()), glm::vec3(0.0f, 1.0f, 0.0f)));
                postTransformHands();
            }
            _model.updateHitbox(_rotation);
            Uniforms uni = draw(shader);
			if (_weapon){
                weaponTransformation(uni);
				_weapon->animate(shader);
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
            rot = glm::rotate(rot, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::vec3 limbpos = _position + glm::vec3(transformation * glm::vec4(limb->position(), 1.0f) * glm::inverse(_rotation));
            _weapon->setPosition(limbpos);
            _weapon->setRotation(_rotation * rot);
            // uni.add_uni("pos", limbpos);
            // uni.add_uni("fRotation", rot);s
        }

	private:
		Weapon* _weapon = nullptr;

		short _health = 10;
		short _energy = 10;
        float _speed = 0.1;
		float _walk = 0.1;
		float _run = 0.2;
		short _jump = 30;

	private:
		glm::vec3 _velocity = glm::vec3(0.0f);
		glm::vec3 _collision = glm::vec3(0.0f); //Don't really need floats for this
};
