#include "settings.hpp"
#include "Player.hpp"

Settings::Settings() : width_(), height_() {}

void Settings::setWindow(GLFWwindow *win) { window_ = win; }
void Settings::setWidth(int width) { width_ = width; }
void Settings::setHeight(int height) { height_ = height; }

GLFWwindow*         Settings::window() const { return window_; }
int			        Settings::width() const { return width_; }
int			        Settings::height() const { return height_; }