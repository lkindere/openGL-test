#pragma once

#include "Camera.hpp"
#include "Model.hpp"

extern Camera camera;

class Object
{
	public:
		Object(const Model& model);

    public:
        void draw(const Shader& shader, const glm::vec3& pos = glm::vec3(0.0f),
            const glm::vec3& scale = glm::vec3(1.0f), const glm::mat4& rotation = glm::mat4(1.0f));

    private:
		Model _model;
};
