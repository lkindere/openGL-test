#include "Uniforms.hpp"

void Uniforms::add_uni(const char*name, int flag){
    flags |= flag;
}

void Uniforms::add_uni(const char*name, const glm::vec3& data){
    std::vector<glm::vec3> vec(1, data);
    vec3[name] = vec;
}

void Uniforms::add_uni(const char*name, const glm::vec4& data){
    std::vector<glm::vec4> vec(1, data);
    vec4[name] = vec;
}

void Uniforms::add_uni(const char*name, const glm::mat4& data){
    std::vector<glm::mat4> vec(1, data);
    mat4[name] = vec;
}

void Uniforms::add_uni(const char*name, const std::vector<glm::vec3>& vec){
    vec3[name] = vec;
}

void Uniforms::add_uni(const char*name, const std::vector<glm::vec4>& vec){
    vec4[name] = vec;
}

void Uniforms::add_uni(const char*name, const std::vector<glm::mat4>& vec){
    mat4[name] = vec;
}