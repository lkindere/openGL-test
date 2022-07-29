#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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

		void setFOV(float FOV) { FOV_ = FOV; }
		void setNear(float near) { near_ = near; }
		void setFar(float far) { far_ = far; }

		void setMode(e_mode mode) { mode_ = mode; }
		
		//Flags
		void set(e_flags flag) { flags_ |= flag; }
		void unset(e_flags flag) { flags_ &= ~flag; }
		
		//				GET
		//Parameters
		GLFWwindow* window() const { return window_; }
		int			width() const { return width_; }
		int			height() const { return height_; }

		float		FOV() { return FOV_; }
		float		near() { return near_; }
		float		far() { return far_;  }

		e_mode		mode() const { return mode_; }
		
		//Flags
		int		flags() const { return flags_; }
		bool	isSet(e_flags flag) { return (flags_ & flag); }

	private:
		Settings& operator=(const Settings& s);
		Settings(const Settings& s);

	private:
		GLFWwindow*	window_;
		int			width_;
		int			height_;
		float		FOV_;
		float		near_;
		float		far_;

		e_mode		mode_;
		int			flags_;
};