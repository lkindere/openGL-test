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
		void Matrix(const glm::vec3& position, const glm::vec3& direction);
		void addShader(Shader& shader);
		glm::vec3 updateDirection();

	public:
		std::vector<Shader>	shaders;

		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);

		float yaw = -90.0f;
		float pitch = 0.0f;

		glm::mat4 cameraMatrix = glm::mat4(1.0f);

		float speed = 0.05f;
};