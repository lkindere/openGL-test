#include "Model.hpp"
#include "Scene.hpp"

Model::Model(MeshData data, int ID, int shader, Scene* scene)
    : _VAO(data), _animator(data), _ID(ID), _shaderID(shader),
        _scene(scene), _hitboxBase(std::move(data.hitbox.vertices)) {
    if (data.texture.data != nullptr)
        _flags |= hasTextures;
    if (data.nBones != 0)
        _flags |= hasBones;
}

void Model::draw(Uniforms uniforms){  
    _VAO.bind();
    const Shader* shader = _scene->shader(_shaderID);
    shader->bind();
    shader->update(uniforms);
    glUniform1i(glGetUniformLocation(shader->ID(), "modelFlags"), _flags);
    glUniform1i(glGetUniformLocation(shader->ID(), "boneTransforms"), 1);
    
    std::cout << "Drawing instanced, size:" << _instances.size() << std::endl;
    _VAO.updateInstances(_instances, _instanceBones);
    // glDrawElements(GL_TRIANGLES, _VAO.nIndices(), GL_UNSIGNED_INT, (void*)0);
    glDrawElementsInstanced(GL_TRIANGLES, _VAO.nIndices(), GL_UNSIGNED_INT, (void*)0, _instances.size());
    _VAO.deleteInstanceBuffer();

    shader->unbind();
    _VAO.unbind();
}

BufferData Model::buffer(const InstanceData& instance, const modelIN& in){
    _instances.push_back(instance);
    if (_flags & hasBones){
        std::vector<glm::mat4> newBones(generateMatrices(in));
        auto it = _instanceBones.insert(_instanceBones.end(), newBones.begin(), newBones.end());
        return BufferData(_instanceBones, it - _instanceBones.begin());
    }
    return BufferData(_instanceBones, -1);
}

void Model::clearBuffer(){
    _instances.clear();
    _instanceBones.clear();
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
