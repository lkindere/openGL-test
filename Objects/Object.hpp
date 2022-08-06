#pragma once

#include "Camera.hpp"
#include "Model.hpp"

extern Camera camera;

class Object
{
	public:
		Object(const Model& model)
			: _model(model) {}
        void draw(Shader& shader, const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f), const glm::mat4& rotation = glm::mat4(1.0f)){
			Uniforms uni;
			uni.vec3 = {
				std::make_pair("pos", pos),
				std::make_pair("scale", scale)
			};
			uni.mat4 = {
				std::make_pair("rotation", rotation),
                std::make_pair("camPos", camera.matrix())
			};
			_model.draw(shader, uni);
		}
	private:
		Object& operator=(const Object& p);
		Object(const Object& p);

    private:
		Model _model;
};
