#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"
#include "Model.hpp"

extern Settings settings;
extern Camera camera;

class Light
{
	public:
		Light(const Model& model);

    public:
		void addTarget(Shader& target);
		void draw(Shader& shader);

	private:
		std::vector<Shader>	_targets;
		Model				_model;

		glm::vec4 color = glm::vec4(1.0f, 0.3f, 0.3f, 1.0f);
		glm::vec3 pos = glm::vec3(0.0f, 10.0f, 0.0f);
};
