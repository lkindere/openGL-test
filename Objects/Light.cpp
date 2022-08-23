#include "Light.hpp"
#include "Scene.hpp"

Light::Light(MeshData data, Scene* scene)
    : Object(&data, scene){
    setPosition(0.0f, 20.0f, 0.0f);
}

void Light::setDefaultUniforms(){
    _uniforms.flags = _flags;
    _uniforms.add_uni("pos", _position);
    _uniforms.add_uni("scale", _scale);
    _uniforms.add_uni("lightColor", _color);
    _uniforms.add_uni("camPos", _scene->camera().matrix());
}

void Light::addTarget(Shader& target){
    _targets.push_back(target);
}

void Light::animate()
{
    for (auto it = _targets.begin(); it != _targets.end(); ++it){
        it->bind();
        glUniform3fv(glGetUniformLocation(it->ID(), "lightPos"), 1, glm::value_ptr(_position));
        glUniform4fv(glGetUniformLocation(it->ID(), "lightColor"), 1, glm::value_ptr(_color));
    }
    glUseProgram(0);
    draw();
}
