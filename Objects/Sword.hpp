#pragma once

#include "settings.hpp"
#include "ArrayObject.hpp"

// #include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include <glm/gtx/rotate_vector.hpp>
// #include <glm/gtx/vector_angle.hpp>
// #include <glm/gtx/transform.hpp>

extern Settings settings;
class Sword
{		//
	public:
		Sword(){
			const glm::vec3 tip_color = glm::vec3(0.15, 0.40, 0.15);
			const glm::vec3 edge_color = glm::vec3(0.40, 0.15, 0.15);
			const glm::vec3 blade_color = glm::vec3(0.2, 0.2, 0.2);
			const glm::vec3 handle_color = glm::vec3(0.3, 0.1, 0.1);
			
			const float tip_len = 0.3;

			const float blade_len = 1.0;
			const float blade_width = 0.05;
			const float edge_width = 0.025;
			const float blade_thick = 0.025;

			const float base_len = 0.1;
			const float base_width = 0.15;
			const float handle_len = 0.4 / 2;
			
			std::vector<Vert2v3> vertices =
			{//						 X								Y											Z					/V3 color
				Vert2v3{glm::vec3(	0.0,						handle_len + base_len + blade_len + tip_len,	0.0),				tip_color},		//Blade tip 0

																																					//Blade front
				Vert2v3{glm::vec3(	-blade_width,					handle_len + base_len,						-blade_thick),		blade_color},	//Bot left	1
				Vert2v3{glm::vec3(	-blade_width,					handle_len + base_len + blade_len,			-blade_thick),		blade_color},	//Top left	2
				Vert2v3{glm::vec3(	blade_width,					handle_len + base_len,						-blade_thick),		blade_color},	//Bot right	3 
				Vert2v3{glm::vec3(	blade_width,					handle_len + base_len + blade_len,			-blade_thick),		blade_color},	//Top right	4
	
																																					//Blade back
				Vert2v3{glm::vec3(	-blade_width,					handle_len + base_len,						blade_thick),		blade_color},	//Bot left	5
				Vert2v3{glm::vec3(	-blade_width,					handle_len + base_len + blade_len,			blade_thick),		blade_color},	//Top left	6 
				Vert2v3{glm::vec3(	blade_width,					handle_len + base_len,						blade_thick),		blade_color},	//Bot right	7
				Vert2v3{glm::vec3(	blade_width,					handle_len + base_len + blade_len,			blade_thick),		blade_color},	//Top right	8

																																					//Blade left
				Vert2v3{glm::vec3(	-(blade_width + edge_width),	handle_len + base_len + blade_len,			0.0),				edge_color},	//Top		9 
				Vert2v3{glm::vec3(	-(blade_width + edge_width),	handle_len + base_len,						0.0),				edge_color},	//Bot		10
				Vert2v3{glm::vec3(	-(blade_width + edge_width),	handle_len + base_len + (blade_len / 2),	0.0),				edge_color},	//Mid		11

																																					//Blade right
				Vert2v3{glm::vec3(	(blade_width + edge_width),		handle_len + base_len + blade_len,			0.0),				edge_color},	//Top		12
				Vert2v3{glm::vec3(	(blade_width + edge_width),		handle_len + base_len,						0.0),				edge_color},	//Bot		13
				Vert2v3{glm::vec3(	(blade_width + edge_width),   	handle_len + base_len + (blade_len / 2),	0.0),				edge_color},	//Mid		14
				
																																					//Base front
				Vert2v3{glm::vec3(	-base_width,					handle_len + base_len,						-blade_thick),		handle_color},	//Top left	15
				Vert2v3{glm::vec3(	-base_width,					handle_len,									-blade_thick),		handle_color},	//Bop left	16
				Vert2v3{glm::vec3(	base_width,						handle_len + base_len, 						-blade_thick),		handle_color},	//Top right	17
				Vert2v3{glm::vec3(	base_width,						handle_len,									-blade_thick),		handle_color},	//Bot right	18

																																					//Base back
				Vert2v3{glm::vec3(	-base_width,					handle_len + base_len, 						blade_thick),		handle_color},	//Top left	19
				Vert2v3{glm::vec3(	-base_width,					handle_len,									blade_thick),		handle_color},	//Bot left	20
				Vert2v3{glm::vec3(	base_width,						handle_len + base_len,						blade_thick),		handle_color},	//Top right	21
				Vert2v3{glm::vec3(	base_width,						handle_len,									blade_thick),		handle_color},	//Bot right	22

																																					//Handle front
				Vert2v3{glm::vec3(	-blade_width,					-handle_len,								-blade_thick),		handle_color},	//Top left	23
				Vert2v3{glm::vec3(	-blade_width,					handle_len,									-blade_thick),		handle_color},	//Bot left	24
				Vert2v3{glm::vec3(	blade_width,					-handle_len,								-blade_thick),		handle_color},	//Top right	25
				Vert2v3{glm::vec3(	blade_width,					handle_len,									-blade_thick),		handle_color},	//Bot right	26

																																					//Handle back
				Vert2v3{glm::vec3(	-blade_width,					-handle_len,								blade_thick),		handle_color},	//Top left	27
				Vert2v3{glm::vec3(	-blade_width,					handle_len,									blade_thick),		handle_color},	//Bot left	28
				Vert2v3{glm::vec3(	blade_width,					-handle_len,								blade_thick),		handle_color},	//Top right	29
				Vert2v3{glm::vec3(	blade_width,					handle_len,									blade_thick),		handle_color},	//Bot right	30

			};
			std::vector<GLuint> indices =
			{
				//Tip back/front
				0, 2, 4,
				0, 6, 8,
				//Tip left/right
				0, 9, 2,
				0, 9, 6,	
				0, 12, 4,
				0, 12, 8,

				//Blade front
				1, 2, 3,
				2, 3, 4,
				//Blade back
				5, 6, 7,
				6, 7, 8,
				// Blade front left side
				9, 10, 1,
				9, 10, 2,
				11, 1, 2,
				//Blade front right side
				12, 13, 3,
				12, 13, 4,
				14, 3, 4,
				//Blade back left side
				9, 10, 5,
				9, 10, 6,
				11, 5, 6,
				//Blade back right side
				12, 13, 7,
				12, 13, 8,
				14, 7, 8,

				//Base front
			    15, 16, 17,
				16, 17, 18,
				// //Base back
				19, 20, 21,
				20, 21, 22,
				//Base left
				19, 20, 15,
				15, 16, 20,	
				//Base right
				21, 22, 17,
				17, 18, 22,
				//Base bottom
				16, 18, 20,
				22, 20, 18,
				//Base top
				15, 17, 19,
				21, 19, 17, 

				//Handle front
				23, 24, 25,
				24, 25, 26,
				//Handle back
				27, 28, 29,
				28, 29, 30,
				// Handle left
				23, 24, 27,
				27, 28, 24,
				//Handle right
				25, 26, 29,
				29, 30, 26,
				//Handle bottom
				24, 26, 28,
				28, 30, 26,
			};
			VAO.init(vertices, indices);
			_indices = indices.size();
		}
		void draw(Shader& shader){
			VAO.bind();
if (settings.mode() == first_person){
			//MOUSE
			float mscale = 2;
			double mouseX;
			double mouseY;
			glfwGetCursorPos(settings.window(), &mouseX, &mouseY);
			//Scale to down to 0.0 -> 2.0
			mouseX = mouseX / (settings.width() / 2);
			mouseY = mouseY / (settings.height() / 2);
			//Decrement to -1.0 -> 1.0 range
			mouseX -= 1;
			mouseY -= 1;
			//Scale by scalar
			mouseX *= mscale;
			mouseY *= mscale;
			//Store mouse vec3 on uniform
			glm::vec3 pos(mouseX , -mouseY - 1.0, 1.0);
			glUniform3fv(glGetUniformLocation(shader.getID(), "pos"), 1, glm::value_ptr(pos));

			//Projection
    		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
   			glm::vec3 Center = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 Position = glm::vec3(0.0f, 0.0f, 2.0f);

			glm::mat4 view = glm::lookAt(Position, Center, Up);
			glm::mat4 projection = glm::perspective(glm::radians(settings.FOV()), 1.0f, settings.near(), settings.far());
			glm::mat4 posMatrix = projection * view;
			glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "camPos"), 1, GL_FALSE, glm::value_ptr(posMatrix));

			//Rotation
			glm::mat4 rotMatrix(1.0f);
			rotMatrix = glm::rotate(rotMatrix, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
			glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rotMatrix));
}
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