#pragma once

#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "settings.hpp"

extern Settings settings;

enum cameraMode
{
    first_person = 0,
    detached = 1
};

class Camera {
	public:
		Camera();

	public:
		void setPosition(const glm::vec3& position);
        void updateProjection();

	public:
		glm::mat4   matrix() const;
		glm::vec3   mouseDirection();

	public:
        void                setMode(cameraMode mode){
            _mode = mode;
        }
        cameraMode          mode() const { return _mode; }
        const glm::vec3&    position() const;
        const glm::vec3&    direction() const;
		const glm::vec3&    up() const;
		const glm::vec3&    front() const;
		float               yaw() const;
		float               pitch() const;

	private:
        cameraMode  _mode = first_person;
		glm::mat4 _projection = glm::mat4(1.0f);

		glm::vec3 _position = glm::vec3(0.0f);
		glm::vec3 _direction = glm::vec3(0.0f, 0.0f, 1.0f);

		float _yaw = 0.0f;
		float _pitch = 0.0f;

		const glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
		const glm::vec3 _front = glm::vec3(0.0f, 0.0f, -1.0f);
		const float _FOV = 100.0f;
		const float _near = 0.1f;
		const float _far = 1000.0f;
        const float _speed = 0.05f;
};