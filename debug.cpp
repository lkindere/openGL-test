#include "debug.hpp"

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
