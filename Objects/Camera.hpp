#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <vector>

#include "Shader.hpp"

class Camera {
	public:
		Camera();
		void Matrix();
		void Inputs();
		void addShader(Shader& shader);

	private:
		void matrix_freeFloat();
		void matrix_firstPerson();
		void input_freeFloat();
		void input_firstPerson();

	private:
		std::vector<Shader>	shaders;
		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 1.0f);
    	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);

		float speed = 0.05f;
		float sensitivity = 100.0f;

		bool firstClick = true;
};