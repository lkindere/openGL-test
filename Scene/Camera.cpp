#include "Camera.hpp"

Camera::Camera() {}

void Camera::input(){
    if (glfwGetKey(settings.window(), GLFW_KEY_W) == GLFW_PRESS)
        _position += _speed * _direction;
    if (glfwGetKey(settings.window(), GLFW_KEY_S) == GLFW_PRESS)
        _position += _speed * -_direction;
    if (glfwGetKey(settings.window(), GLFW_KEY_A) == GLFW_PRESS)
        _position += _speed * glm::normalize(glm::cross(-_direction, _up));
    if (glfwGetKey(settings.window(), GLFW_KEY_D) == GLFW_PRESS)
        _position += _speed * glm::normalize(glm::cross(_direction, _up));
    mouseDirection();
}

void Camera::updateProjection() {
    _projection = glm::perspective(
	    glm::radians(_FOV), (float)settings.width() / settings.height(), _near, _far);
}

void Camera::setPosition(const glm::vec3& position) {
	_position = position;
}

glm::mat4 Camera::matrix() const {
	glm::mat4 view(glm::lookAt(_position, _position + _direction, _up));
	return glm::mat4(_projection * view);
}

glm::vec3 Camera::mouseDirection() {
	glfwSetInputMode(settings.window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	double mouseX;
	double mouseY;
	glfwGetCursorPos(settings.window(), &mouseX, &mouseY);
	float offsetX = (mouseX - settings.width() / 2) * _speed;
	float offsetY = (settings.height() / 2 - mouseY) * _speed;
	glfwSetCursorPos(settings.window(), (settings.width() / 2), (settings.height() / 2)); 
	_yaw += offsetX;
	_pitch += offsetY;
	if (_mode == first_person && _pitch > 35.0f)
	        _pitch =  35.0f;
    else if (_pitch > 80.0f)
        _pitch = 80.0f;
	if(_mode == first_person && _pitch < -35.0f)
	    _pitch = -35.0f;
    else if (_pitch < -80.0f)
        _pitch = -80.0f;
	_direction = glm::vec3(cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)),
		sin(glm::radians(_pitch)), sin(glm::radians(_yaw)) * cos(glm::radians(_pitch)));
	return glm::normalize(_direction);
}

void                Camera::setMode(cameraMode mode){ _mode = mode; }

const glm::vec3&    Camera::position() const { return _position; }
const glm::vec3&    Camera::direction() const { return _direction; }
const glm::vec3&    Camera::up() const { return _up; }
const glm::vec3&    Camera::front() const { return _front; }
float               Camera::yaw() const { return _yaw; }
float               Camera::pitch() const { return _pitch; }