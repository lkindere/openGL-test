#include "Light.hpp"

Light::Light(Model model)
    : Object(&model){
    setPosition(0.0f, 20.0f, 0.0f);
}

void Light::addTarget(Shader& target){
    _targets.push_back(target);
}

void Light::animate(Shader& shader)
{
    for (auto it = _targets.begin(); it != _targets.end(); ++it){
        it->bind();
        glUniform3fv(glGetUniformLocation(it->ID(), "lightPos"), 1, glm::value_ptr(_position));
        glUniform4fv(glGetUniformLocation(it->ID(), "lightColor"), 1, glm::value_ptr(_color));
    }
    glUseProgram(0);
    Uniforms uni;
    uni.add_uni("lightColor", _color);
    draw(shader, uni);
}
