#include "Animator.hpp"

#include "Scene.hpp"

Animator::Animator(MeshData& data)
    : _timers(std::move(data.timers)), _nodes(std::move(data.nodes)),
        _matrices(data.nBones, glm::mat4(1.0f)){
    calculateBase(_nodes, glm::mat4(1.0f));
}

void Animator::calculateBase(const NodeData& node, const glm::mat4& last){
    glm::mat4 nodeTransform = node.transformation;
    glm::mat4 globalTransform = last * nodeTransform;
    if (node.bone != nullptr)
        _matrices[node.bone->ID] = globalTransform * node.bone->offset;
    for (auto i = 0; i < node.children.size(); ++i)
        calculateBase(node.children[i], globalTransform);
}

//Depending on the usage of find node might want to restructure more efficiently
const NodeData* Animator::findNode(const char* name) const{
    return traverseNodes(name, _nodes);
}

const NodeData* Animator::traverseNodes(const char*name, const NodeData& node) const{
    if (node.name == name)
        return &node;
    for (auto i = 0; i < node.children.size(); ++i){
        const NodeData* ptr = traverseNodes(name, node.children[i]);
        if (ptr != nullptr)
            return ptr;
    }
    return nullptr;
}

const std::vector<glm::mat4>&   Animator::matrices() const {
    return _matrices;
}

float                           Animator::duration(int ID) const {
    return _timers[ID].duration / _timers[ID].tps;
}

float Animator::getTick(int anim, float time, bool loop){
    if (anim < 0 || anim + 1 > _timers.size())
        return -1;
    time *= _timers[anim].tps;
    if (time >= _timers[anim].duration){
        if (!loop)
            return -1;
        time = fmod(time, _timers[anim].duration);
    }
    return time;
}

std::vector<glm::mat4> Animator::generateMatrices(const modelIN& input){
    aData data;
    data.tick = getTick(input.anim, input.time, input.loop);
    if (input.postTransforms.size() == 0 && data.tick == -1)
        return _matrices;
    data.output = std::vector<glm::mat4>(_matrices.size(), glm::mat4(1.0f));
    data.input = &input;
    calculateNodes(_nodes, glm::mat4(1.0f), data);
    return data.output;
}

void Animator::calculateNodes(const NodeData& node, const glm::mat4& last, aData& data){
    glm::mat4 nodeTransform = node.transformation;
    if (node.bone != nullptr){
        if (node.bone->animations.size() != 0 && data.tick != -1)
            nodeTransform = currentMatrix(node.bone.get(), data.input->anim, data.tick);
        auto it = data.input->postTransforms.find(node.name);
        if (it != data.input->postTransforms.end())
            nodeTransform *= it->second;
    }
    glm::mat4 globalTransform = last * nodeTransform;
    if (node.bone != nullptr)
        data.output[node.bone->ID] = globalTransform * node.bone->offset;
    for (auto i = 0; i < node.children.size(); ++i)
        calculateNodes(node.children[i], globalTransform, data);
}

glm::mat4 Animator::currentMatrix(const BoneData* bone, int anim, float tick) const {
    glm::mat4 pos = currentPos(bone->animations[anim].positions, tick);
    glm::mat4 rot = currentRot(bone->animations[anim].rotations, tick);
    glm::mat4 scale = currentScale(bone->animations[anim].scales, tick);
    return (pos * rot * scale);
}

glm::mat4 Animator::currentPos(const std::vector<KeyPosition>& positions, float time) const {
    if (positions.size() == 0){
        std::cout << "NO POSITIONS\n";
        assert(0);
    }
    if (positions.size() == 1)
        return glm::translate(glm::mat4(1.0f), positions[0].position);
    const KeyPosition* last = &positions[0];
    const KeyPosition* next = &positions[1];
    for (auto i = 1; i < positions.size() - 1; ++i){
        if (positions[i].timestamp > time)
            break ;
        last = &positions[i];
        next = &positions[i + 1];
    }
    return glm::translate(glm::mat4(1.0f), glm::mix(last->position, next->position,
        getInterpolant(time, last->timestamp, next->timestamp)));
}

glm::mat4 Animator::currentRot(const std::vector<KeyRotation>& rotations, float time) const {
    if (rotations.size() == 0){
        std::cout << "NO ROTATIONS\n";
        assert(0);
    }
    if (rotations.size() == 1)
        return glm::toMat4(glm::normalize(rotations[0].rotation));
    const KeyRotation* last = &rotations[0];
    const KeyRotation* next = &rotations[1];
    for (auto i = 1; i < rotations.size() - 1; ++i){
        if (rotations[i].timestamp > time)
            break ;
        last = &rotations[i];
        next = &rotations[i + 1];
    }
    return glm::toMat4(glm::normalize(glm::slerp(last->rotation, next->rotation,
        getInterpolant(time, last->timestamp, next->timestamp))));
}

glm::mat4 Animator::currentScale(const std::vector<KeyScale>& scales, float time) const {
    if (scales.size() == 0){
        std::cout << "NO SCALES\n";
        assert(0);
    }
    if (scales.size() == 1)
        return glm::translate(glm::mat4(1.0f), scales[0].scale);
    const KeyScale* last = &scales[0];
    const KeyScale* next = &scales[1];
    for (auto i = 1; i < scales.size() - 1; ++i){
        if (scales[i].timestamp > time)
            break ;
        last = &scales[i];
        next = &scales[i + 1];
    }
    return glm::scale(glm::mat4(1.0f), glm::mix(last->scale, next->scale,
        getInterpolant(time, last->timestamp, next->timestamp)));
}

float Animator::getInterpolant(float time, float t1, float t2) const {
    return ((time - t1) / (t2 - t1));
}