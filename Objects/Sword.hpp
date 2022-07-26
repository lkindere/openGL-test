#pragma once

#include "ArrayObject.hpp"

class Sword
{
	public:
		Sword(){
			std::vector<Vert2v3> vertices =
			{
				Vert2v3{glm::vec3(-0.075, -0.5, 0.0), glm::vec3(0.2, 0.2, 0.2)}, //Blade
				Vert2v3{glm::vec3(-0.075,  0.5, 0.0), glm::vec3(0.2, 0.2, 0.2)},
				Vert2v3{glm::vec3( 0.075, -0.5, 0.0), glm::vec3(0.2, 0.2, 0.2)},
				Vert2v3{glm::vec3( 0.075,  0.5, 0.0), glm::vec3(0.2, 0.2, 0.2)},
				Vert2v3{glm::vec3( 0.0,    0.6, 0.0), glm::vec3(0.2, 0.2, 0.2)}, //Blade tip
				Vert2v3{glm::vec3(-0.15,  -0.5, 0.0), glm::vec3(0.4, 0.1, 0.1)}, //Base
				Vert2v3{glm::vec3(-0.15,  -0.6, 0.0), glm::vec3(0.4, 0.1, 0.1)},
				Vert2v3{glm::vec3( 0.15,  -0.5, 0.0), glm::vec3(0.4, 0.1, 0.1)},
				Vert2v3{glm::vec3( 0.15,  -0.6, 0.0), glm::vec3(0.4, 0.1, 0.1)},
				Vert2v3{glm::vec3(-0.05, -0.6, 0.0), glm::vec3(0.4, 0.1, 0.1)}, //Handle
				Vert2v3{glm::vec3(-0.05, -0.8, 0.0), glm::vec3(0.4, 0.1, 0.1)},
				Vert2v3{glm::vec3( 0.05, -0.6, 0.0), glm::vec3(0.4, 0.1, 0.1)},
				Vert2v3{glm::vec3( 0.05, -0.8, 0.0), glm::vec3(0.4, 0.1, 0.1)},
			};
			std::vector<GLuint> indices =
			{
				//Blade
				0, 1, 2,
				1, 2, 3,
				//Blade tip
				1, 3, 4,
				//Base
			    5, 6, 7,
				6, 7, 8,
				//Handle
				9, 10, 11,
				10, 11, 12,
			};
			VAO.init(vertices, indices);
			_indices = indices.size();
		}
		void draw(){
			VAO.bind();
			glDrawElements(GL_TRIANGLES, _indices, GL_UNSIGNED_INT, (void*)0);
			VAO.unbind();
		}
	private:
		const short damage = 10;
		const short range = 10;
		const short speed = 10;
		ArrayObject<Vert2v3> VAO;
		short _indices;
};