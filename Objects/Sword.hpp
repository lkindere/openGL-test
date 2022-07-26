#pragma once

#include "ArrayObject.hpp"

class Sword
{		//
	public:
		Sword(){
			const glm::vec3 tip_color = glm::vec3(0.15, 0.50, 0.15);
			const glm::vec3 blade_color = glm::vec3(0.2, 0.2, 0.2);
			const glm::vec3 handle_color = glm::vec3(0.3, 0.1, 0.1);
			
			const float tip_len = 0.5 / 2;

			const float blade_len = 1.0 / 2;
			const float blade_width = 0.1 / 2;
			const float edge_width = 0.05 / 2;
			const float blade_thick = 0.05 / 2;

			const float base_len = 0.2 / 2;
			const float base_width = 0.3 / 2;
			const float handle_len = 0.4 / 2;
			
			std::vector<Vert2v3> vertices =
			{						 //X							/Y											/Z					/Vec 3 color
																																				  //Blade front
				Vert2v3{glm::vec3(	-blade_width,					-blade_len,									-blade_thick),		blade_color}, //[0]Bot left
				Vert2v3{glm::vec3(	-blade_width,					blade_len,									-blade_thick),		blade_color}, //[1]Top left
				Vert2v3{glm::vec3(	 blade_width,					-blade_len,									-blade_thick),		blade_color}, //[2]Bot right
				Vert2v3{glm::vec3(	blade_width,					blade_len,									-blade_thick),		blade_color}, //[3]Top right
				
				Vert2v3{glm::vec3(	0.0,							(blade_len + tip_len),						0.0),				tip_color}, //[4] Blade tip

																					//Base front
				Vert2v3{glm::vec3(	-base_width,					-blade_len,									-blade_thick),		handle_color}, //[5]Top left
				Vert2v3{glm::vec3(	-base_width,					-(blade_len + base_len),					-blade_thick),		handle_color}, //[6]Bot left
				Vert2v3{glm::vec3(	base_width,						-blade_len, 								-blade_thick),		handle_color}, //[7]Top right
				Vert2v3{glm::vec3(	base_width,						-(blade_len + base_len),					-blade_thick),		handle_color}, //[8]Bot right

																					//Handle front
				Vert2v3{glm::vec3(	-blade_width,					-(blade_len + base_len),					-blade_thick),		handle_color}, //[9]
				Vert2v3{glm::vec3(	-blade_width,					-(blade_len + base_len + handle_len),		-blade_thick),		handle_color}, //[10]
				Vert2v3{glm::vec3(	blade_width,					-(blade_len + base_len),					-blade_thick),		handle_color}, //[11]
				Vert2v3{glm::vec3(	blade_width,					-(blade_len + base_len + handle_len),		-blade_thick),		handle_color}, //[12]

																					//Blade front left side
				Vert2v3{glm::vec3(	-(blade_width + edge_width),	blade_len,									0.0),				blade_color}, //[13]Top
				Vert2v3{glm::vec3(	-(blade_width + edge_width),	-blade_len,									0.0),				blade_color}, //[14]Bot
				Vert2v3{glm::vec3(	-(blade_width + edge_width),	0.0,										0.0),				blade_color}, //[15]Mid

																					//Blade front right side
				Vert2v3{glm::vec3(	(blade_width + edge_width),		blade_len,									0.0),				blade_color}, //[16]Top
				Vert2v3{glm::vec3(	(blade_width + edge_width),		-blade_len,									0.0),				blade_color}, //[17]Bot
				Vert2v3{glm::vec3(	(blade_width + edge_width),   	 0.0,										0.0),				blade_color}, //[18]Mid

																					//Blade back
				Vert2v3{glm::vec3(	-blade_width,					-blade_len,									blade_thick),		blade_color}, //[19]Bot left
				Vert2v3{glm::vec3(	-blade_width,					blade_len,									blade_thick),		blade_color}, //[20]Top left
				Vert2v3{glm::vec3(	blade_width,					-blade_len,									blade_thick),		blade_color}, //[21]Bot right
				Vert2v3{glm::vec3(	blade_width,					blade_len,									blade_thick),		blade_color}, //[22]Top right

																					//Base back
				Vert2v3{glm::vec3(	-base_width,					-blade_len, 								blade_thick),		handle_color}, //[23]Top left
				Vert2v3{glm::vec3(	-base_width,					-(blade_len + base_len),					blade_thick),		handle_color}, //[24]Bot left
				Vert2v3{glm::vec3(	base_width,						-blade_len,									blade_thick),		handle_color}, //[25]Top right
				Vert2v3{glm::vec3(	base_width,						-(blade_len + base_len),					blade_thick),		handle_color}, //[26]Bot right

																					//Handle back
				Vert2v3{glm::vec3(	-blade_width,					-(blade_len + base_len),					blade_thick),		handle_color}, //[27]
				Vert2v3{glm::vec3(	-blade_width,					-(blade_len + base_len + handle_len),		blade_thick),		handle_color}, //[28]
				Vert2v3{glm::vec3(	blade_width,					-(blade_len + base_len),					blade_thick),		handle_color}, //[29]
				Vert2v3{glm::vec3(	blade_width,					-(blade_len + base_len + handle_len),		blade_thick),		handle_color}, //[30]

			};
			std::vector<GLuint> indices =
			{
				//Tip back/front
				1, 3, 4,
				20, 22, 4,
				//Tip left/right
				4, 13, 1,
				4, 13, 20,	
				4, 16, 3,
				4, 16, 22,

				//Blade front
				0, 1, 2,
				1, 2, 3,
				//Blade front left side
				13, 14, 0,
				13, 14, 1,
				15, 0, 1,
				//Blade front right side
				16, 17, 2,
				16, 17, 3,
				18, 2, 3,
				//Blade back
				19, 20, 21,
				20, 21, 22,
				//Blade back left side
				13, 14, 19,
				13, 14, 20,
				//Blade back right side
				16, 17, 21,
				16, 17, 22,
				18, 20, 21,

				//Base front
			    5, 6, 7,
				6, 7, 8,
				// //Base back
				23, 24, 25,
				24, 25, 26,
				//Base left
				23, 24, 5,
				5, 6, 24,
				//Base right
				25, 26, 7,
				7, 8, 26,
				//Base bottom
				6, 8, 24,
				26, 24, 8,
				//Base top
				5, 7, 23,
				25, 23, 7, 

				//Handle front
				9, 10, 11,
				10, 11, 12,
				//Handle back
				27, 28, 29,
				28, 29, 30,
				// Handle left
				9, 10, 27,
				27, 28, 10,
				//Handle right
				11, 12, 29,
				29, 30, 12,
				//Handle bottom
				10, 12, 28,
				28, 30, 12,

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