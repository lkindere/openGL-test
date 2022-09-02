#pragma once

#include "main.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Settings
{
	public:
		Settings();
		
		void setWindow(GLFWwindow *win);
		void setWidth(int width);
		void setHeight(int height);

		GLFWwindow*         window() const;
		int			        width() const;
		int			        height() const;

	private:
		GLFWwindow*	window_;
		int			width_;
		int			height_;
};