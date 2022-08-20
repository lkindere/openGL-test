#pragma once

#include <iostream>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Player;

class Settings
{
	public:
		Settings();
		
		void setWindow(GLFWwindow *win);
		void setWidth(int width);
		void setHeight(int height);
		void setGravity(float gravity);
        void setPlayer(Player* player);

		GLFWwindow*         window() const;
		int			        width() const;
		int			        height() const;
		float               gravity() const;
        const glm::vec3&    playerPosition() const;

	private:
		GLFWwindow*	window_;
        Player*     player_;
		int			width_;
		int			height_;
		float		gravity_;

	public:
		void printvec(const glm::vec3& vec);
		void printvec(const glm::vec4& vec);
		void printmat(const glm::mat3& mat);
		void printmat(const glm::mat4& mat);
};