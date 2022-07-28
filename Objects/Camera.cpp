#include "settings.hpp"

#include "Camera.hpp"
#include <iostream>

extern Settings settings;

Camera::Camera(int width, int height)
    : width(width), height(height) {}

void Camera::Matrix(Shader &shader){
	glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(settings.FOV()), (float)settings.width() / settings.height(), settings.near(), settings.far());

	cameraMatrix = projection * view;

	glm::mat4 rotation(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rotation));
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "camPos"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}
void Camera::Inputs() {
    // Keys
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
			glfwSetCursorPos(settings.window(), (width / 2), (height / 2));
			firstClick = false;
		}
        glfwSetInputMode(settings.window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        double mouseX;
        double mouseY;
        glfwGetCursorPos(settings.window(), &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (height / 2)) / height;

        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f) || (glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))))
			Orientation = newOrientation;

		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		glfwSetCursorPos(settings.window(), (width / 2), (height / 2)); 
	}	
    if (glfwGetMouseButton(settings.window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
        glfwSetInputMode(settings.window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}