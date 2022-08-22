#pragma once

#include <vector>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/gtx/quaternion.hpp>

#include "Structs.hpp"
#include "settings.hpp"

extern Settings settings;

class Animator
{
	public:
		Animator() {}

		void init(MeshData& data){
			_timers = std::move(data.timers);
            _nodes = std::move(data.nodes);
            _matrices = std::vector<glm::mat4>(30, glm::mat4(1.0f));
            timeCurrent = glfwGetTime();
            timeLast = timeCurrent;
		}

		const std::vector<glm::mat4>& updateMatrices(){
            if (_timers.size() == 0)
                return _matrices;
            updateTimers();
            traverseMatrices(_nodes, glm::mat4(1.0f));
			return _matrices;
		}
        
        const glm::mat4& getBoneMatrix(short ID) const {
            return _matrices[ID];
        }

        void postTransform(int ID, const glm::mat4& transform) {
            _matrices[ID] = transform * _matrices[ID];
        }

        void setAnim(int anim) {
            _anim = anim;
            timeLast = glfwGetTime();
        }

        void setLoop(bool loop) { _loop = loop; }

        bool loop() const { return _loop; }
        int anim() const { return _anim; }

        const NodeData* findNode(const char* name){
            return traverseNodes(name, _nodes);
        }

    private:
        const NodeData* traverseNodes(const char*name, const NodeData& node){
            if (node.name == name)
                return &node;
            for (auto i = 0; i < node.children.size(); ++i){
                const NodeData* ptr = traverseNodes(name, node.children[i]);
                if (ptr != nullptr)
                    return ptr;
            }
            return nullptr;
        }

        void updateTimers(){
            timeCurrent = glfwGetTime();
            if ((timeCurrent - timeLast) * _timers[0].tps >= _timers[0].duration){
                (_loop) ?
                    timeLast += _timers[0].duration / _timers[0].tps
                    :   _anim = -1;
            }
            currentTick = (timeCurrent - timeLast) * _timers[0].tps;
        }

        void traverseMatrices(const NodeData& node, const glm::mat4& parentTransform){
            glm::mat4 nodeTransform = node.transformation;
            if (node.bone != nullptr && node.bone->animations.size() != 0){
                if (_anim != -1)
                    nodeTransform = currentMatrix(node.bone.get(), currentTick);
                else if (node.bone->postTransform != nullptr)
                    nodeTransform *= *(node.bone->postTransform);
            }

            glm::mat4 globalTransform = parentTransform * nodeTransform;
            if (node.bone != nullptr)
                _matrices[node.bone->ID] = globalTransform * node.bone->offset;
            for (auto i = 0; i < node.children.size(); ++i)
                traverseMatrices(node.children[i], globalTransform);
        }

        glm::mat4 currentMatrix(const BoneData* bone, float time) const {
            glm::mat4 pos = currentPos(bone->animations[_anim].positions, currentTick);
            glm::mat4 rot = currentRot(bone->animations[_anim].rotations, currentTick);
            glm::mat4 scale = currentScale(bone->animations[_anim].scales, currentTick);
            if (bone->postTransform != nullptr)
                return (*(bone->postTransform) * pos * rot * scale);
            return (pos * rot * scale);
        }

        glm::mat4 currentPos(const std::vector<KeyPosition>& positions, float time) const {
            if (positions.size() == 0)
                std::cout << "NO POSITIONS\n";
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

        glm::mat4 currentRot(const std::vector<KeyRotation>& rotations, float time) const {
            if (rotations.size() == 0)
                std::cout << "NO ROTATIONS\n";
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

        glm::mat4 currentScale(const std::vector<KeyScale>& scales, float time) const {
            if (scales.size() == 0)
                std::cout << "NO SCALES\n";
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

        float getInterpolant(float time, float t1, float t2) const {
	        return ((time - t1) / (t2 - t1));
        }


	private:
        int     _anim = -1;
        bool    _loop = false;
        float   timeLast = 0;
        float   timeCurrent = 0;
        float   currentTick = 0;

    private:
        NodeData                _nodes;
        std::vector<AnimTimers> _timers;
        std::vector<glm::mat4>  _matrices;
};