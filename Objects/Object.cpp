#include "Object.hpp"

Object::Object(const Model& model) : _model(model) {}

void Object::draw(const Shader& shader, const glm::vec3& pos,
                    const glm::vec3& scale, const glm::mat4& rotation){
    Uniforms uni;
    uni.vec3 = {
        make_uni("pos", pos),
        make_uni("scale", scale)
    };
    uni.mat4 = {
        make_uni("rotation", rotation),
        make_uni("camPos", camera.matrix())
    };
    _model.draw(shader, uni);
}
