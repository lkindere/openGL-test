#include "Object.hpp"

Object::Object(Model model) : _model(std::move(model)) {}

void Object::draw(const Shader& shader, const glm::vec3& pos,
                    const glm::vec3& scale, const glm::mat4& rotation){
    Uniforms uni;
    uni.add_uni("pos", pos);
    uni.add_uni("camPos", camera.matrix());
    _model.draw(shader, uni);
}
