#pragma once

#include <map>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

std::pair<const char*, std::vector<glm::vec3> >  make_uni(const char* name, const glm::vec3& data);
std::pair<const char*, std::vector<glm::vec4> >  make_uni(const char* name, const glm::vec4& data);
std::pair<const char*, std::vector<glm::mat4> >  make_uni(const char* name, const glm::mat4& data);
std::pair<const char*, std::vector<glm::vec3> >  make_uni(const char* name, const std::vector<glm::vec3>& vec);
std::pair<const char*, std::vector<glm::vec4> >  make_uni(const char* name, const std::vector<glm::vec4>& vec);
std::pair<const char*, std::vector<glm::mat4> >  make_uni(const char* name, const std::vector<glm::mat4>& vec);

enum flags
{
    hasTextures = 1 << 0,
    hasBones = 1 << 1,
};

struct Uniforms {
    int                                             flags;
    std::map<const char*, std::vector<glm::vec3> >  vec3;
    std::map<const char*, std::vector<glm::vec4> >  vec4;
    std::map<const char*, std::vector<glm::mat4> >  mat4;
};
