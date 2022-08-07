#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

enum e_flags{
	none = 1,
};

class Settings
{
	public:
		Settings() : width_(), height_(), flags_() {}
		
		//				SET
		//Paramaters
		void setWindow(GLFWwindow *win) { window_ = win; }
		void setWidth(int width) { width_ = width; }
		void setHeight(int height) { height_ = height; }

		//Physics
		void setGravity(float gravity) { gravity_ = gravity; }
		
		//Flags
		void set(e_flags flag) { flags_ |= flag; }
		void unset(e_flags flag) { flags_ &= ~flag; }
		
		//				GET
		//Parameters
		GLFWwindow* window() const { return window_; }
		int			width() const { return width_; }
		int			height() const { return height_; }

		//Physics
		float		gravity() { return gravity_; }
		
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
		//Physics
		float		gravity_;
		//Flags
		int			flags_;

    public:
        bool print = false;

	public:
		//For easier debugging
		void printvec(const glm::vec3& vec){
			std::cout << "X: " << vec.x << " Y: " << vec.y << " Z: " << vec.z << std::endl; }
		void printvec(const glm::vec4& vec){
			std::cout << "X: " << vec.x << " Y: " << vec.y << " Z: " << vec.z << " W: " << vec.w << std::endl; }
		void printmat(const glm::mat3& mat){
			printvec(mat[0]);
			printvec(mat[1]);
			printvec(mat[2]);
		}
		void printmat(const glm::mat4& mat){
			printvec(mat[0]);
			printvec(mat[1]);
			printvec(mat[2]);
			printvec(mat[3]);
		}
};