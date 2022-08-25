#include "Model.hpp"

Model::Model(MeshData data, GLenum drawtype)
    : _VAO(data, drawtype), _animator(data), _hitbox(data.hitbox) {}

void Model::draw(const Shader& shader, Uniforms uniforms){  
    if (_VAO.hasTexture())
        uniforms.flags |= hasTextures;
    _VAO.bind();
    shader.bind();
    shader.update(uniforms);

    glDrawElements(GL_TRIANGLES, _VAO.nIndices(), GL_UNSIGNED_INT, (void*)0);

    shader.unbind();
    _VAO.unbind();
}

const NodeData* Model::findNode(const char* name) const{
    return _animator.findNode(name);
}


const Hitbox&                   Model::hitbox() const {
    return _hitbox; 
}

const std::vector<glm::mat4>&   Model::matrices() const {
    return _animator.matrices();
}

float                           Model::duration(int ID) const {
    return _animator.duration(ID);
}

std::vector<glm::mat4> Model::generateMatrices(const modelIN& input){
    return _animator.generateMatrices(input);
}
