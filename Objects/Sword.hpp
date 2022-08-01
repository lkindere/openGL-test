#pragma once

#include "settings.hpp"
#include "ArrayObject.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern Settings settings;

class Sword
{		//
	public:
		Sword(std::vector<Vert>& vertices, std::vector<GLuint>& indices){
			VAO.init(vertices, indices);
			_indices = indices.size();
		}
		void draw(Shader& shader){
			VAO.bind();
			shader.bind();
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
				glm::vec3 scale(0.3f);
				glUniform3fv(glGetUniformLocation(shader.getID(), "pos"), 1, glm::value_ptr(pos));
				glUniform3fv(glGetUniformLocation(shader.getID(), "scale"), 1, glm::value_ptr(scale));

				//Rotation
				rotMatrix = glm::rotate(rotMatrix, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
			}
			glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rotMatrix));
			glDrawElements(GL_TRIANGLES, _indices, GL_UNSIGNED_INT, (void*)0);
			shader.unbind();
			VAO.unbind();
		}
	private:
		const short damage = 10;
		const short range = 10;
		const short speed = 10;
		ArrayObject VAO;
		short _indices;
};