#include "settings.hpp"

#include "Camera.hpp"
#include <iostream>

extern Settings settings;

Camera::Camera() {}

void Camera::Matrix(Shader &shader){
	if (settings.mode() == free_float)
		matrix_freeFloat(shader);
	if (settings.mode() == first_person)
		matrix_firstPerson(shader);
}

void Camera::matrix_freeFloat(Shader &shader){
	glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(settings.FOV()), (float)settings.width() / settings.height(), settings.near(), settings.far());

	cameraMatrix = projection * view;

	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "camPos"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::matrix_firstPerson(Shader &shader){
	glm::vec3 Center = glm::vec3(0.0f);
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 2.0f);

	glm::mat4 view = glm::lookAt(Position, Center, Up);
	glm::mat4 projection = glm::perspective(glm::radians(settings.FOV()), (float)settings.width() / settings.height(), settings.near(), settings.far());
	glm::mat4 posMatrix = projection * view;

	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "camPos"), 1, GL_FALSE, glm::value_ptr(posMatrix));
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
