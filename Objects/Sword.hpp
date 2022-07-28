#pragma once

#include "settings.hpp"
#include "ArrayObject.hpp"
#include "Swordmodel.mod"

// #include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include <glm/gtx/rotate_vector.hpp>
// #include <glm/gtx/vector_angle.hpp>
// #include <glm/gtx/transform.hpp>

extern Settings settings;

class Sword
{		//
	public:
		Sword(){
			SWORDMODEL	//Probably very dirty and stupid way to do this but will be cleaner for now
			VAO.init(vertices, indices);
			_indices = indices.size();
		}
		void draw(Shader& shader){
			VAO.bind();
			glm::mat4 rotMatrix(1.0f);
			if (settings.mode() == first_person){
				//MOUSE
				float mscale = 2;
				double mouseX;
				double mouseY;
				glfwGetCursorPos(settings.window(), &mouseX, &mouseY);
				//Scale to down to 0.0 -> 2.0
				mouseX = mouseX / (settings.width() / 2);
				mouseY = mouseY / (settings.height() / 2);
				//Decrement to -1.0 -> 1.0 range
				mouseX -= 1;
				mouseY -= 1;
				//Scale by scalar
				mouseX *= mscale;
				mouseY *= mscale;
				//Store mouse vec3 on uniform
				glm::vec3 pos(mouseX , -mouseY - 1.0, 1.0);
				glUniform3fv(glGetUniformLocation(shader.getID(), "pos"), 1, glm::value_ptr(pos));

				//Rotation
				rotMatrix = glm::rotate(rotMatrix, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
			}
			glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rotMatrix));
			glDrawElements(GL_TRIANGLES, _indices, GL_UNSIGNED_INT, (void*)0);
			VAO.unbind();
		}
	private:
		const short damage = 10;
		const short range = 10;
		const short speed = 10;
		ArrayObject<Vert2v3> VAO;
		short _indices;
};