#include "settings.hpp"

#include "Camera.hpp"
#include <iostream>

extern Settings settings;

Camera::Camera() {}

void Camera::addShader(Shader& shader){
	shaders.push_back(shader);
}

void Camera::Matrix(){
	if (settings.mode() == free_float)
		matrix_freeFloat();
	if (settings.mode() == first_person)
		matrix_firstPerson();
}

void Camera::matrix_freeFloat(){
	glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(settings.FOV()), (float)settings.width() / settings.height(), settings.near(), settings.far());
	cameraMatrix = projection * view;

	glm::vec3 scale(1.0f);
	for (auto it = shaders.begin(); it != shaders.end(); ++it){
		it->bind();
		glUniform3fv(glGetUniformLocation(it->getID(), "scale"), 1, glm::value_ptr(scale));
		glUniformMatrix4fv(glGetUniformLocation(it->getID(), "camPos"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
		it->unbind();
	}
}

void Camera::matrix_firstPerson(){
	glm::vec3 Center = glm::vec3(0.0f);
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 2.0f);

	glm::mat4 view = glm::lookAt(Position, Center, Up);
	glm::mat4 projection = glm::perspective(glm::radians(settings.FOV()), (float)settings.width() / settings.height(), settings.near(), settings.far());
	glm::mat4 posMatrix = projection * view;
	
	for (auto it = shaders.begin(); it != shaders.end(); ++it){
		it->bind();
		glUniformMatrix4fv(glGetUniformLocation(it->getID(), "camPos"), 1, GL_FALSE, glm::value_ptr(posMatrix));
		it->unbind();
	}
}

void Camera::Inputs() {
	if (settings.mode() == free_float)
		input_freeFloat();
	if (settings.mode() == first_person)
		input_firstPerson();
}

void Camera::input_freeFloat(){
    if (glfwGetKey(settings.window(), GLFW_KEY_W) == GLFW_PRESS)
        Position += speed * Orientation;
    if (glfwGetKey(settings.window(), GLFW_KEY_A) == GLFW_PRESS)
        Position += speed * -glm::normalize(glm::cross(Orientation, Up));
    if (glfwGetKey(settings.window(), GLFW_KEY_S) == GLFW_PRESS)
        Position += speed * -Orientation;
    if (glfwGetKey(settings.window(), GLFW_KEY_D) == GLFW_PRESS)
        Position += speed * glm::normalize(glm::cross(Orientation, Up));
    if (glfwGetKey(settings.window(), GLFW_KEY_SPACE) == GLFW_PRESS)
        Position += speed * Up;
    if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        Position += speed * -Up;
    if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        speed = 0.4f;
    if (glfwGetKey(settings.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        speed = 0.1f;
    // Mouse
    if (glfwGetMouseButton(settings.window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (firstClick){
			glfwSetCursorPos(settings.window(), (settings.width() / 2), (settings.height() / 2));
			firstClick = false;
		}
        glfwSetInputMode(settings.window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        double mouseX;
        double mouseY;
        glfwGetCursorPos(settings.window(), &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseY - (settings.height() / 2)) / settings.height();
        float rotY = sensitivity * (float)(mouseX - (settings.height() / 2)) / settings.height();

        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f) || (glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))))
			Orientation = newOrientation;

		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		glfwSetCursorPos(settings.window(), (settings.width() / 2), (settings.height() / 2)); 
	}	
    if (glfwGetMouseButton(settings.window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
        glfwSetInputMode(settings.window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}

void Camera::input_firstPerson(){

}
