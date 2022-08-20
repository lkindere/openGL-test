#include "settings.hpp"
#include "Player.hpp"

Settings::Settings() : width_(), height_() {}

void Settings::setWindow(GLFWwindow *win) { window_ = win; }
void Settings::setWidth(int width) { width_ = width; }
void Settings::setHeight(int height) { height_ = height; }
void Settings::setGravity(float gravity) { gravity_ = gravity; }
void Settings::setPlayer(Player* player) { player_ = player; }

GLFWwindow*         Settings::window() const { return window_; }
int			        Settings::width() const { return width_; }
int			        Settings::height() const { return height_; }
float		        Settings::gravity() const { return gravity_; }
const glm::vec3&    Settings::playerPosition() const { return player_->position(); }

void Settings::printvec(const glm::vec3& vec){
    std::cout << "X: " << vec.x << " Y: " << vec.y << " Z: " << vec.z << std::endl; }

void Settings::printvec(const glm::vec4& vec){
    std::cout << "X: " << vec.x << " Y: " << vec.y << " Z: " << vec.z << " W: " << vec.w << std::endl; }

void Settings::printmat(const glm::mat3& mat){
    printvec(mat[0]);
    printvec(mat[1]);
    printvec(mat[2]);
}

void Settings::printmat(const glm::mat4& mat){
    printvec(mat[0]);
    printvec(mat[1]);
    printvec(mat[2]);
    printvec(mat[3]);
}
