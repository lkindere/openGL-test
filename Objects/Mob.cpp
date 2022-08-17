#include "Mob.hpp"
#include <glm/gtx/vector_angle.hpp>

Mob::Mob(Model model) : _model(std::move(model)) {
    _model.setAnim(0);
    _model.setLoop(true);
}

void Mob::draw(const Shader& shader){
    Uniforms uni;
    move(uni);
    uni.add_uni("pos", position);
    uni.add_uni("camPos", camera.matrix());
    _model.draw(shader, uni);
}

void Mob::move(Uniforms& uni){
    glm::vec3 direction = glm::normalize(glm::vec3(camera.position().x, 0.0f, camera.position().z) - position);
    glm::mat4 rotation = glm::transpose(glm::lookAt(position, camera.position(), glm::vec3(0.0f, 1.0f, 0.0f)));
    std::cout << "Rotation:\n";
    settings.printmat(rotation);
    std::cout << std::endl;
    uni.add_uni("fRotation", rotation);
    position += glm::vec3(direction.x, 0.0f, direction.z) * (speed / 20);
}
