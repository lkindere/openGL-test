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

class Sword : public Weapon
{		//
	public:
		Sword(std::vector<Vert>& vertices, std::vector<GLuint>& indices){
			VAO.init(vertices, indices);
			_indices = indices.size();
		}
		void draw(Shader& shader, const glm::vec3& pos, const glm::vec3& dir){
			glm::vec3 scale(1.0f);
			glm::mat4 rotation(1.0f);
			glm::vec3 drawpos = pos + dir * glm::vec3(3.0f, 3.0f, 3.0f);
						// glm::vec3 drawpos = pos + dir * glm::vec3(0.0f, 0.0f, 3.0f);
			glUniform3fv(glGetUniformLocation(shader.getID(), "pos"), 1, glm::value_ptr(drawpos));
			glUniform3fv(glGetUniformLocation(shader.getID(), "scale"), 1, glm::value_ptr(scale));
            glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rotation));
            glDrawElements(GL_TRIANGLES, _indices, GL_UNSIGNED_INT, (void*)0);
		}
	private:
		const short damage = 10;
		const short range = 10;
		const short speed = 10;
		ArrayObject VAO;
		short _indices;
};