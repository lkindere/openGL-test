#pragma once

#include "Sword.hpp"
#include "Camera.hpp"

extern Settings settings;

class Player
{
	public:
		Player(std::vector<Vert> vertices, std::vector<GLuint> indices)
			: health(10), energy(10), speed(0.1), walk(0.1), run(0.2), jump(30)
			, position(0.0f, 10.0f, 0.0f), direction(0.0, 0.0, 1.0), weapon(nullptr) {
            VAO.init(vertices, indices);
			_indices = indices.size();
        }
		void input() {
			direction.y = 0;
			if (glfwGetKey(settings.window(), GLFW_KEY_W) == GLFW_PRESS)
				position += speed * direction;
			if (glfwGetKey(settings.window(), GLFW_KEY_S) == GLFW_PRESS)
				position -= speed * direction;
			if (glfwGetKey(settings.window(), GLFW_KEY_A) == GLFW_PRESS)
				position -= speed * glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(settings.window(), GLFW_KEY_D) == GLFW_PRESS)
				position += speed * glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
			if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				speed = run;
			if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
				speed = walk;
			if (glfwGetKey(settings.window(), GLFW_KEY_SPACE) == GLFW_PRESS && collision.y){
				collision.y = 0;
				velocity.y = settings.gravity() * jump;
			}
			direction = camera.updateDirection();
			physics();
		}
        
		void physics(){
			if (!collision.y){
				velocity.y -= settings.gravity();
				position.y += velocity.y;
				if (position.y <= 2.0){
					position.y = 2.0;
					velocity.y = 0;
					collision.y = 1;
				}
			}
		}

		void setWeapon(Weapon* wep){
			delete weapon;
			weapon = wep;
		}

        void draw(Shader& shader){
			VAO.bind();
			shader.bind();
			if (weapon)
				weapon->draw(shader, position, direction);
			// Reset campos
			camera.Matrix(position, direction);
			shader.unbind();
			VAO.unbind();
		}
	private:
		Player& operator=(const Player& p);
		Player(const Player& p);
		
	public:
		Camera camera;

	private:
		Weapon* weapon;
		short health;
		short energy;
        float speed;
		float walk;
		float run;
		short jump;
    
    private:
        glm::vec3 position;
		glm::vec3 direction;

        ArrayObject VAO;
        short _indices;

	private:
		glm::vec3 velocity = glm::vec3(0.0f);
		glm::vec3 collision = glm::vec3(0.0f); //Don't really need floats for this
};
