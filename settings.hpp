#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

enum e_mode{
	free_float = 0,
	first_person = 1,
};

enum e_flags{
	none = 1,
};

class Settings
{
	public:
		Settings() : width_(), height_(), mode_(), flags_() {}
		
		//				SET
		//Paramaters
		void setWindow(GLFWwindow *win) { window_ = win; }
		void setWidth(int width) { width_ = width; }
		void setHeight(int height) { height_ = height; }

		//Camera
		void setFOV(float FOV) { FOV_ = FOV; }
		void setNear(float near) { near_ = near; }
		void setFar(float far) { far_ = far; }

		void setMode(e_mode mode) { mode_ = mode; }

		//Physics
		void setGravity(float gravity) { gravity_ = gravity; }

		//Data
		void setPlayerPos(glm::vec3 position) { playerPos_ = position; }
		
		//Flags
		void set(e_flags flag) { flags_ |= flag; }
		void unset(e_flags flag) { flags_ &= ~flag; }
		
		//				GET
		//Parameters
		GLFWwindow* window() const { return window_; }
		int			width() const { return width_; }
		int			height() const { return height_; }

		//Camera
		float		FOV() { return FOV_; }
		float		near() { return near_; }
		float		far() { return far_;  }

		e_mode		mode() const { return mode_; }

		//Physics
		float		gravity() { return gravity_; }

		//Data
		glm::vec3	playerPos() { return playerPos_; }
		
		//Flags
		int			flags() const { return flags_; }
		bool		isSet(e_flags flag) { return (flags_ & flag); }

	private:
		Settings& operator=(const Settings& s);
		Settings(const Settings& s);

	private:
		//Window
		GLFWwindow*	window_;
		int			width_;
		int			height_;
		//Camera
		float		FOV_;
		float		near_;
		float		far_;
		//Physics
		float		gravity_;
		//Data
		glm::vec3	playerPos_;

		e_mode		mode_;
		int			flags_;

	public:
		void printvec(glm::vec3 vec){
			std::cout << "X: " << vec.x << " Y: " << vec.y << " Z: " << vec.z << std::endl; }
		void printvec(glm::vec4 vec){
			std::cout << "X: " << vec.x << " Y: " << vec.y << " Z: " << vec.z << " W: " << vec.w << std::endl; }
};