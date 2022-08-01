#pragma once

#include "settings.hpp"
#include "ArrayObject.hpp"

extern Settings settings;

class Light
{
	public:
		Light(std::vector<Vert>& vertices, std::vector<GLuint>& indices){
			VAO.init(vertices, indices);
			_indices = indices.size();
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
			glDrawElements(GL_TRIANGLES, _indices, GL_UNSIGNED_INT, (void*)0);
			shader.unbind();
			VAO.unbind();
		}
	private:
		std::vector<Shader>	targets;
		glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 pos = glm::vec3(0.0f, 5.0f, 0.0f);
		ArrayObject VAO;
		short _indices;
};
