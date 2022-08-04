#pragma once

#include "settings.hpp"
#include "Weapon.hpp"
#include "ArrayObject.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"

extern Settings settings;

extern float g_pitch;
extern float g_yaw;



#include <unistd.h>

class Sword : public Weapon
{		//
	public:
		Sword(const char* path){
			VAO.init(path);
		}
		void attack(Shader& shader, const glm::vec3& pos, const glm::vec3& dir){
			// collisions(pos, dir);
			static int cooldown;
			float framecount = 20;
			static float frame;
			static float offset;
			static glm::mat4 frot(1.0f);

			if (--cooldown > 0)
				return ;
			if (!attacking)
				return ;
			std::cout << "Offset: " << offset << std::endl;
			if (frame < 7 || frame > framecount - 7)	//Tilt to the right
				frot = glm::rotate(frot, glm::radians(offset * 4), glm::vec3(1.0f, 0.0f, 0.0f));
			if (frame < 5 || frame > framecount - 5) //Rotate sideways
				frot = glm::rotate(frot, glm::radians(offset * 3), glm::vec3(0.0f, 1.0f, 0.0f));
			if ((frame > 4 && frame < 10) || (frame < framecount - 4 && frame > 10)) //Slash to the left
				frot = glm::rotate(frot, glm::radians(offset * 3), glm::vec3(0.0f, 0.0f, -1.0f));
			
			glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "fRotation"), 1, GL_FALSE, glm::value_ptr(frot));

			glUniform3fv(glGetUniformLocation(shader.getID(), "fOffset"), 1, glm::value_ptr(glm::vec3(0.5f - abs(offset) / 10, -0.5f - abs(offset) / 20, 0.0f)));

			std::cout << "Frame: " << frame << std::endl;
			if (offset == framecount / 2)
				offset *= -1;
			++offset;
			if (++frame >= framecount){
				frame = 0;
				offset = 0;
				attacking = false;
				frot = glm::mat4(1.0f);
				cooldown = 20;
				std::cout << std::endl;
			}
		}

		void draw(Shader& shader, const glm::vec3& pos, const glm::vec3& dir){
			glm::vec3 scale(0.05f);
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(g_yaw), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::vec3 drawpos = pos + dir;
			glUniform3fv(glGetUniformLocation(shader.getID(), "fOffset"), 1, glm::value_ptr(glm::vec3(0.5f, -0.5f, 0.0f)));
			glUniform3fv(glGetUniformLocation(shader.getID(), "pos"), 1, glm::value_ptr(drawpos));
			glUniform3fv(glGetUniformLocation(shader.getID(), "scale"), 1, glm::value_ptr(scale));
            glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rotation));

			if (glfwGetMouseButton(settings.window(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
				attacking = true;
			attack(shader, pos, dir);
            glDrawElements(GL_TRIANGLES, VAO.nIndices(), GL_UNSIGNED_INT, (void*)0);

			//Reset offset
			glUniform3fv(glGetUniformLocation(shader.getID(), "fOffset"), 1, glm::value_ptr(glm::vec3(0.0f)));
			glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "fRotation"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		}
	private:
		const short damage = 10;
		const short range = 10;
		const short speed = 10;
		ArrayObject VAO;
		bool attacking = true;
};