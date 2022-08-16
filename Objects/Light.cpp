#include "Light.hpp"

Light::Light(const Model& model) : _model(model) {}

void Light::addTarget(Shader& target){
    _targets.push_back(target);
}
void Light::draw(Shader& shader){
    //Export lightColor to all target shaders
    for (auto it = _targets.begin(); it != _targets.end(); ++it){
        it->bind();
        glUniform3fv(glGetUniformLocation(it->ID(), "lightPos"), 1, glm::value_ptr(pos));
        glUniform4fv(glGetUniformLocation(it->ID(), "lightColor"), 1, glm::value_ptr(color));
        it->unbind();
    }
    //Export lightColor to self + draw light
    Uniforms uni;
    uni.add_uni("pos", pos);
    uni.add_uni("lightColor", color);
    uni.add_uni("camPos", camera.matrix());
    _model.draw(shader, uni);
}
