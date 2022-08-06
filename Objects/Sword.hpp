#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ArrayObject.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Weapon.hpp"

#include "settings.hpp"

extern Settings settings;
extern Camera camera;

#include <unistd.h>

class Sword : public Weapon
{		//
	public:
		Sword(const Model& model)
			: _model(model) {}
		void attack(Shader& shader, const glm::vec3& pos, const glm::vec3& dir){
			// // collisions(pos, dir);
			// static int cooldown;
			// float framecount = 20;
			// static float frame;
			// static float offset;
			// static glm::mat4 frot(1.0f);

			// if (--cooldown > 0)
			// 	return ;
			// if (!attacking)
			// 	return ;
			// if (frame < 7 || frame > framecount - 7)	//Tilt to the right
			// 	frot = glm::rotate(frot, glm::radians(offset * 4), glm::vec3(1.0f, 0.0f, 0.0f));
			// if (frame < 5 || frame > framecount - 5) //Rotate sideways
			// 	frot = glm::rotate(frot, glm::radians(offset * 3), glm::vec3(0.0f, 1.0f, 0.0f));
			// if ((frame > 4 && frame < 10) || (frame < framecount - 4 && frame > 10)) //Slash to the left
			// 	frot = glm::rotate(frot, glm::radians(offset * 3), glm::vec3(0.0f, 0.0f, -1.0f));
			
			// glUniformMatrix4fv(glGetUniformLocation(shader.ID(), "fRotation"), 1, GL_FALSE, glm::value_ptr(frot));

			// glUniform3fv(glGetUniformLocation(shader.ID(), "fOffset"), 1, glm::value_ptr(glm::vec3(0.5f - abs(offset) / 10, -0.5f - abs(offset) / 20, 0.0f)));

			// if (offset == framecount / 2)
			// 	offset *= -1;
			// ++offset;
			// if (++frame >= framecount){
			// 	frame = 0;
			// 	offset = 0;
			// 	attacking = false;
			// 	frot = glm::mat4(1.0f);
			// 	cooldown = 20;
			// 	std::cout << std::endl;
			// }
		}

		void draw(Shader& shader, const glm::vec3& pos, const glm::vec3& dir){
			glm::vec3 scale(0.05f);
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(camera.yaw()), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::vec3 drawpos = pos + dir;

			Uniforms uni;
			uni.vec3 = {
				std::make_pair("fOffset", glm::vec3(0.5f, -0.5f, 0.0f)),
				std::make_pair("pos", drawpos),
				std::make_pair("scale", scale)
			};
			uni.mat4 = {
				std::make_pair("rotation", rotation),
                std::make_pair("camPos", camera.matrix())
			};
			// if (glfwGetMouseButton(settings.window(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
			// 	attacking = true;
			// attack(shader, pos, dir);
			_model.draw(shader, uni);
		}
	private:
		const short damage = 10;
		const short range = 10;
		const short speed = 10;
		Model _model;
		bool attacking = true;
};