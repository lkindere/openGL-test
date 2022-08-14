#include "Uniforms.hpp"

std::pair<const char*, std::vector<int> >        make_uni(const char* name, int data){
    std::vector<int> vec(1, data);
    return std::make_pair(name, vec);
}

std::pair<const char*, std::vector<glm::vec3> >  make_uni(const char* name, const glm::vec3& data){
    std::vector<glm::vec3>  vec(1, data);
    return std::make_pair(name, vec);
}

std::pair<const char*, std::vector<glm::vec4> >  make_uni(const char* name, const glm::vec4& data){
    std::vector<glm::vec4>  vec(1, data);
    return std::make_pair(name, vec);
}

std::pair<const char*, std::vector<glm::mat4> >  make_uni(const char* name, const glm::mat4& data){
    std::vector<glm::mat4>  vec(1, data);
    return std::make_pair(name, vec);
}

std::pair<const char*, std::vector<int> >        make_uni(const char* name, const std::vector<int>& vec){
    return std::make_pair(name, vec);
}

std::pair<const char*, std::vector<glm::vec3> >  make_uni(const char* name, const std::vector<glm::vec3>& vec){
    return std::make_pair(name, vec);
}

std::pair<const char*, std::vector<glm::vec4> >  make_uni(const char* name, const std::vector<glm::vec4>& vec){
    return std::make_pair(name, vec);
}

std::pair<const char*, std::vector<glm::mat4> >  make_uni(const char* name, const std::vector<glm::mat4>& vec){
    return std::make_pair(name, vec);
}
