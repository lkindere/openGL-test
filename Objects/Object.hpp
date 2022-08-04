#pragma once

#include "ArrayObject.hpp"

extern Settings settings;

class Object
{
	public:
		Object(const char* path) {
            VAO.init(path);
        }
        void draw(Shader& shader, const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f), const glm::mat4& rotation = glm::mat4(1.0f)){
			VAO.bind();
			shader.bind();
			glUniform3fv(glGetUniformLocation(shader.getID(), "pos"), 1, glm::value_ptr(pos));
			glUniform3fv(glGetUniformLocation(shader.getID(), "scale"), 1, glm::value_ptr(scale));
            glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rotation));
            glDrawElements(GL_TRIANGLES, VAO.nIndices(), GL_UNSIGNED_INT, (void*)0);
			shader.unbind();
			VAO.unbind();
		}
	private:
		Object& operator=(const Object& p);
		Object(const Object& p);

    private:
        ArrayObject VAO;
};
