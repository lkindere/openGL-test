#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"
#include "Model.hpp"

extern Settings settings;
extern Camera camera;

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
				glUniform3fv(glGetUniformLocation(it->ID(), "lightPos"), 1, glm::value_ptr(pos));
				glUniform4fv(glGetUniformLocation(it->ID(), "lightColor"), 1, glm::value_ptr(color));
				it->unbind();
			}
			//Export lightColor to self + draw light
			Uniforms uni;
			uni.vec3 = {
				std::make_pair("scale", glm::vec3(0.2f)),
				std::make_pair("pos", pos)
			};
			uni.vec4 = {
				std::make_pair("lightColor", color)
			};
            uni.mat4 = {
                std::make_pair("camPos", camera.matrix())
            };
			_model.draw(shader, uni);
		}
	private:
		glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		glm::vec3 pos = glm::vec3(0.0f, 5.0f, 0.0f);

	private:
		std::vector<Shader>	_targets;
		Model				_model;
};
