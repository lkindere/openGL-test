#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "Model.hpp"

extern Settings settings;

class Light
{
	public:
		Light(const Model& model)
			:	_model(model) {}
		void addTarget(Shader& target){
			_targets.push_back(target);
		}
		void draw(Shader& shader){
			//Export lightColor to all target shaders
			for (auto it = _targets.begin(); it != _targets.end(); ++it){
				it->bind();
				glUniform3fv(glGetUniformLocation(it->getID(), "lightPos"), 1, glm::value_ptr(pos));
				glUniform4fv(glGetUniformLocation(it->getID(), "lightColor"), 1, glm::value_ptr(color));
				it->unbind();
			}
			//Export lightColor to self + draw light
			shader.bind();
			glUniform3fv(glGetUniformLocation(shader.getID(), "scale"), 1, glm::value_ptr(glm::vec3(0.2f)));
			glUniform3fv(glGetUniformLocation(shader.getID(), "pos"), 1, glm::value_ptr(pos));
			glUniform4fv(glGetUniformLocation(shader.getID(), "lightColor"), 1, glm::value_ptr(color));
			_model.draw();
			shader.unbind();
		}
	private:
		glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 pos = glm::vec3(0.0f, 5.0f, 0.0f);

	private:
		std::vector<Shader>	_targets;
		Model				_model;
};
