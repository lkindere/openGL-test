#pragma once

#include "Model.hpp"

class Object
{
	public:
		Object(const Model& model)
			: _model(model) {}
        void draw(Shader& shader, const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f), const glm::mat4& rotation = glm::mat4(1.0f)){
			shader.bind();
			glUniform3fv(glGetUniformLocation(shader.getID(), "pos"), 1, glm::value_ptr(pos));
			glUniform3fv(glGetUniformLocation(shader.getID(), "scale"), 1, glm::value_ptr(scale));
            glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rotation));

			glUniform3fv(glGetUniformLocation(shader.getID(), "fOffset"), 1, glm::value_ptr(glm::vec3(0.0f)));
			glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "fRotation"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
			_model.draw();
			shader.unbind();
		}
	private:
		Object& operator=(const Object& p);
		Object(const Object& p);

    private:
		Model _model;
};
