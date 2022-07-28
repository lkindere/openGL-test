#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

// #include <glm/glm.hpp>
// #include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.hpp"

class Camera {
	public:
		Camera();
		void Matrix(Shader& shader);
		void Inputs();

	private:
		void matrix_freeFloat(Shader& shader);
		void matrix_firstPerson(Shader& shader);
		void input_freeFloat();
		void input_firstPerson();

	private:
		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 1.0f);
    	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);

		float speed = 0.05f;
		float sensitivity = 100.0f;

		bool firstClick = true;
};