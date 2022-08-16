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

		void init(const MeshData& data){
			_timers = data.timers;
            _nodes = data.nodes;
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
        
        const glm::mat4& getBoneMatrix(int ID) const {
            return _matrices[ID];
        }

        void setAnim(int anim){ currentAnim = anim; }

    private:
        // int findBoneID(const char* name, const NodeData& node) const {
        //     if (node.name == name && node.bone)
        //         return node.bone->ID;
        //     for (auto i = 0; i < node.children.size(); ++i){
        //         int ID = findBoneID(name, node.children[i]);
        //         if (ID != -1)
        //             return ID;
        //     }
        //     return -1;
        // }

        void updateTimers(){
            timeCurrent = glfwGetTime();
            if ((timeCurrent - timeLast) * _timers[0].tps >= _timers[0].duration)
                timeLast += _timers[0].duration / _timers[0].tps;
            currentTick = (timeCurrent - timeLast) * _timers[0].tps;
        }

        void traverseMatrices(const NodeData& node, const glm::mat4& parentTransform){
            glm::mat4 nodeTransform = node.transformation;
            if (node.bone != nullptr && node.bone->animations.size() != 0)
                nodeTransform = currentMatrix(node.bone, currentTick);

            glm::mat4 globalTransform = parentTransform * nodeTransform;
            if (node.bone != nullptr)
                _matrices[node.bone->ID] = globalTransform * node.bone->offset;
            for (auto i = 0; i < node.children.size(); ++i)
                traverseMatrices(node.children[i], globalTransform);
        }

        glm::mat4 currentMatrix(const BoneData* bone, float time) const {
            glm::mat4 pos = currentPos(bone->animations[0].positions, currentTick);
            glm::mat4 rot = currentRot(bone->animations[0].rotations, currentTick);
            glm::mat4 scale = currentScale(bone->animations[0].scales, currentTick);
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
        int currentAnim = -1;
        float timeLast = 0;
        float timeCurrent = 0;
        float currentTick = 0;
        std::vector<AnimTimers> _timers;
        NodeData                _nodes;
        std::vector<glm::mat4>  _matrices;
};