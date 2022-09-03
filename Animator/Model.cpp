#include "Model.hpp"

Model::Model(MeshData data, int ID, GLenum drawtype)
    : _VAO(data, drawtype), _animator(data), _ID(ID),
        _hitboxBase(std::move(data.hitbox.vertices)) {}

void Model::draw(const Shader& shader, Uniforms uniforms){  
    if (_VAO.hasTexture())
        uniforms.flags |= hasTextures;
    _VAO.bind();
    shader.bind();
    if (_instances.size() > 1)
        uniforms.flags |= isInstanced;
    shader.update(uniforms);

    if (_instances.size() > 1){
        std::cout << "Drawing instanced\n";
        _VAO.updateInstances(_instances);
        // glDrawElementsInstanced(GL_TRIANGLES, _VAO.nIndices(), GL_UNSIGNED_INT, (void*)0, _instances.size());
    }
    else
        glDrawElements(GL_TRIANGLES, _VAO.nIndices(), GL_UNSIGNED_INT, (void*)0);

    shader.unbind();
    _VAO.unbind();
}

void Model::buffer(const InstanceData& instance){
    _instances.push_back(instance);
}

void Model::clearBuffer(){
    _instances.clear();
}

const NodeData* Model::findNode(const char* name) const{
    return _animator.findNode(name);
}

const std::vector<glm::vec3>&   Model::hitboxBase() const {
    return _hitboxBase;
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
