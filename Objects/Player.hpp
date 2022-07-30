#pragma once

#include "Sword.hpp"

extern Settings settings;

class Player
{
	public:
		Player(std::vector<Vert2v3> vertices, std::vector<GLuint> indices) : health(10), energy(10), speed(1.0), position(0.0), orientation(0.0, 1.0, 0.0) {
            VAO.init(vertices, indices);
			_indices = indices.size();
        }
		void input() {
		}
        
        void draw(Shader& shader){
			VAO.bind();
			glm::mat4 rotMatrix(1.0f);

			glm::vec3 pos(0.0);
			glUniform3fv(glGetUniformLocation(shader.getID(), "pos"), 1, glm::value_ptr(pos));
            glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rotMatrix));

            // #ifdef POINTS
            	// glPointSize(10);
			    // glDrawElements(GL_POINTS, _indices, GL_UNSIGNED_INT, (void*)0);
            // #endif
            #ifndef POINTS
                glDrawElements(GL_TRIANGLES, _indices, GL_UNSIGNED_INT, (void*)0);
            #endif
			VAO.unbind();
		}
	private:
		Player& operator=(const Player& p);
		Player(const Player& p);
		
	private:
		// Sword sword;
		short health;
		short energy;
        float speed;
    
    private:
        glm::vec3 position;
        glm::vec3 orientation;

        ArrayObject<Vert2v3> VAO;
        short _indices;
};
