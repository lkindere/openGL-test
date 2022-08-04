#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "settings.hpp"
#include "ArrayObject.hpp"

extern Settings settings;

class Light
{
	public:
		Light(const char* path){
			VAO.init(path);
		}
		void addTarget(Shader& target){
			targets.push_back(target);
		}
		void draw(Shader& shader){
			//Export lightColor to all target shaders
			for (auto it = targets.begin(); it != targets.end(); ++it){
				it->bind();
				glUniform3fv(glGetUniformLocation(it->getID(), "lightPos"), 1, glm::value_ptr(pos));
				glUniform4fv(glGetUniformLocation(it->getID(), "lightColor"), 1, glm::value_ptr(color));
				it->unbind();
			}
			//Export lightColor to self + draw light
			VAO.bind();
			shader.bind();
			glUniform3fv(glGetUniformLocation(shader.getID(), "scale"), 1, glm::value_ptr(glm::vec3(0.2f)));
			glUniform3fv(glGetUniformLocation(shader.getID(), "pos"), 1, glm::value_ptr(pos));
			glUniform4fv(glGetUniformLocation(shader.getID(), "lightColor"), 1, glm::value_ptr(color));
			glDrawElements(GL_TRIANGLES, VAO.nIndices(), GL_UNSIGNED_INT, (void*)0);
			shader.unbind();
			VAO.unbind();
		}
	private:
		std::vector<Shader>	targets;
		glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 pos = glm::vec3(0.0f, 5.0f, 0.0f);
		ArrayObject VAO;
};
