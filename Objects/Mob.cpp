#include "Mob.hpp"

Mob::Mob(const Model& model) : _model(model) {}

void Mob::draw(const Shader& shader){
    Uniforms uni;
    uni.add_uni("pos", position);
    uni.add_uni("camPos", camera.matrix());
    _model.draw(shader, uni);
    // move();
}

void Mob::move(){
    direction = camera.position() - position;
    direction.y = 0.0f;
    position += direction * (speed / 20);
}
