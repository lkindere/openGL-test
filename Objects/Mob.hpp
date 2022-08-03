#pragma once

#include "Camera.hpp"
#include "settings.hpp"

extern Settings settings;
class Mob
{
	public:
		Mob(std::vector<Vert> vertices, std::vector<GLuint> indices)
			: health(10), energy(10), speed(0.1), weapon(nullptr)
			, position(5.0f, 0.0f, 5.0f), direction(0.0, 0.0, 1.0) {
            VAO.init(vertices, indices);
			_indices = indices.size();
        }
		// void setWeapon(Weapon* wep){
		// 	delete weapon;
		// 	weapon = wep;
		// }

        void draw(Shader& shader){
			VAO.bind();
			shader.bind();

			glUniform3fv(glGetUniformLocation(shader.getID(), "pos"), 1, glm::value_ptr(position));
			glUniform3fv(glGetUniformLocation(shader.getID(), "scale"), 1, glm::value_ptr(glm::vec3(0.01f)));
            glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

            glDrawElements(GL_TRIANGLES, _indices, GL_UNSIGNED_INT, (void*)0);
			shader.unbind();
			VAO.unbind();
			move();
		}
		void move(){
			settings.printvec(direction);
			direction = settings.playerPos() - position;
			direction.y = 0.0f;
			position += direction * (speed / 10);
		}

	private:
		Mob& operator=(const Mob& p);
		Mob(const Mob& p);
		
	public:
		Camera camera;

	private:
		Weapon* weapon;
		short health;
		short energy;
        float speed;
    
    private:
        glm::vec3 position;
		glm::vec3 direction;

        ArrayObject VAO;
        short _indices;
};
