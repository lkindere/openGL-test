#include "Mob.hpp"

Mob::Mob(const Model& model) : _model(model) {}

void Mob::draw(const Shader& shader){
    Uniforms uni;
    uni.vec3 = {
        make_uni("pos", position),
        // make_uni("pos", glm::vec3(5.0f, 0.0f, 0.0f)),
        make_uni("scale", glm::vec3(1.0f))
    };
    uni.mat4 = {
        // make_uni("rotation", rotation),
        make_uni("camPos", camera.matrix())
    };
    _model.draw(shader, uni);
    // move();
}

void Mob::move(){
    direction = camera.position() - position;
    direction.y = 0.0f;
    position += direction * (speed / 20);
}
