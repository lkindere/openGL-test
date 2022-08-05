#pragma once

#include "Model.hpp"

#include "settings.hpp"

extern Settings settings;
class Mob
{
	public:
		Mob(const Model& model)
			: _model(model) {}
		// void setWeapon(Weapon* wep){
		// 	delete weapon;
		// 	weapon = wep;
		// }

        void draw(Shader& shader){
			shader.bind();
			glUniform3fv(glGetUniformLocation(shader.getID(), "pos"), 1, glm::value_ptr(position));
			glUniform3fv(glGetUniformLocation(shader.getID(), "scale"), 1, glm::value_ptr(glm::vec3(0.01f)));
            glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

			glUniform3fv(glGetUniformLocation(shader.getID(), "fOffset"), 1, glm::value_ptr(glm::vec3(0.0f)));
			glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "fRotation"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
			_model.draw();
			shader.unbind();
			move();
		}
		void move(){
			direction = settings.playerPos() - position;
			direction.y = 0.0f;
			position += direction * (speed / 10);
		}

	private:
		Mob& operator=(const Mob& p);
		Mob(const Mob& p);

	private:
		Weapon* weapon = nullptr;
		short health = 10;
		short energy = 10;
        float speed = 0.1;
    
    private:
        glm::vec3 position = glm::vec3(5.0f, 0.0f, 5.0f);
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);

        Model _model;
};
