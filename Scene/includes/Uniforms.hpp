#pragma once

#include "main.hpp"

enum flags
{
    hasTextures = 1 << 0,
    hasBones = 1 << 1,
};

struct Uniforms {
    int                                             flags = 0;
    std::map<const char*, float>                    f1;
    std::map<const char*, std::vector<glm::vec3> >  vec3;
    std::map<const char*, std::vector<glm::vec4> >  vec4;
    std::map<const char*, std::vector<glm::mat4> >  mat4;

    public: 
        void add_uni(const char*name, int flag);
        void add_uni(const char*name, float f1);
        void add_uni(const char*name, const glm::vec3& data);
        void add_uni(const char*name, const glm::vec4& data);
        void add_uni(const char*name, const glm::mat4& data);
        void add_uni(const char*name, const std::vector<glm::vec3>& vec);
        void add_uni(const char*name, const std::vector<glm::vec4>& vec);
        void add_uni(const char*name, const std::vector<glm::mat4>& vec);
    };
