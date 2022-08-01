#include "settings.hpp"

#include "Camera.hpp"
#include <iostream>

extern Settings settings;

Camera::Camera() {}

void Camera::addShader(Shader& shader){
	shaders.push_back(shader);
}

void Camera::Matrix(const glm::vec3& position, const glm::vec3& direction){
    glm::mat4 projection(glm::perspective(glm::radians(settings.FOV()), (float)settings.width() / settings.height(), settings.near(), settings.far()));
	glm::mat4 view(glm::lookAt(position, position + direction, Up));
	glm::mat4 cameraMatrix = projection * view;

	for (auto it = shaders.begin(); it != shaders.end(); ++it){
		it->bind();
		glUniformMatrix4fv(glGetUniformLocation(it->getID(), "camPos"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	}
	glUseProgram(0); 
}

glm::vec3 Camera::updateDirection(){
	std::cout << "Shaders: " << std::endl;
	for (auto it = shaders.begin(); it != shaders.end(); ++it)
		std::cout << "Shader: " << it->getID() << std::endl;
	glfwSetInputMode(settings.window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	double mouseX;
	double mouseY;
	glfwGetCursorPos(settings.window(), &mouseX, &mouseY);
	float offsetX = (mouseX - settings.width() / 2) * speed;
	float offsetY = (settings.height() / 2 - mouseY) * speed;
	glfwSetCursorPos(settings.window(), (settings.width() / 2), (settings.height() / 2)); 
	yaw += offsetX;
	pitch += offsetY;
		if(pitch > 89.0f)
	pitch =  89.0f;
		if(pitch < -89.0f)
	pitch = -89.0f;
	glm::vec3 direction(cos(glm::radians(yaw)) * cos(glm::radians(pitch)), sin(glm::radians(pitch)), sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
	return glm::normalize(direction);
}
