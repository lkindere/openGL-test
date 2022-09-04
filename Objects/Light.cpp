#include "Light.hpp"
#include "Scene.hpp"

Light::Light(const std::shared_ptr<Model>& modelptr, Scene* scene, int ID)
    : Object(modelptr, scene, ID){
    setPosition(0.0f, 20.0f, 0.0f);
}

// void Light::setDefaultUniforms(){
//     _uniforms.flags = _flags;
//     _uniforms.add_uni("pos", _position);
//     _uniforms.add_uni("scale", _scale);
//     _uniforms.add_uni("lightColor", _color);
//     _uniforms.add_uni("camPos", _scene->camera().matrix());
// }

void Light::loop()
{
    for (auto i = 0; i < _scene->nShaders(); ++i){
        _scene->shader(i)->bind();
        glUniform3fv(glGetUniformLocation(_scene->shader(i)->ID(), "lightPos"), 1, glm::value_ptr(_position));
        glUniform4fv(glGetUniformLocation(_scene->shader(i)->ID(), "lightColor"), 1, glm::value_ptr(_color));
    }
    // draw();
}
