#pragma once

#include <vector>
#include <iostream>

#include <glm/gtx/quaternion.hpp>

#include "Structs.hpp"
#include "settings.hpp"

extern Settings settings;


class Animator
{
	public:
		Animator() {}

		void init(const MeshData& data) {
			_timers = data.timers;
            _bones = data.bones;
            _transformation = data.transformation;
		}
		
		const std::vector<glm::mat4>& updateMatrices(){
            if (_timers.size() == 0)
                return _matrices;
			if (currentTick > _timers[0].duration)
                currentTick -= _timers[0].duration;
            _matrices.clear();
            _matrices.insert(_matrices.begin(), _bones.size(), _transformation);
			for (auto i = 0; i < _bones.size(); ++i){
                _matrices[i] = _matrices[i] * currentMatrix(_bones[i], currentTick);
                // _matrices[i] =  currentMatrix(_bones[i], currentTick) * _matrices[i];
                for (auto j = 0; j < _bones[i].children.size(); ++j){
                    _matrices[_bones[i].children[j]] = _matrices[i];
                }
				// _matrices[i] = _matrices[i] * _bones[i].offset;
                _matrices[i] = _bones[i].offset * _matrices[i];
            }
            currentTick += 5;
			return _matrices;
		}
        
        const glm::mat4& meshTransform() const {
            return _transformation;
        }

    private:
        glm::mat4 currentMatrix(const BoneData& bone, float time) const {
            static int i;
            if (bone.animations.size() == 0)
                return glm::mat4(1.0f);
            glm::mat4 pos = currentPos(bone.animations[0].positions, currentTick);
            glm::mat4 rot = currentRot(bone.animations[0].rotations, currentTick);
            glm::mat4 scale = currentScale(bone.animations[0].scales, currentTick);
        // if (settings.print){
        //     std::cout << "\n";
        //     std::cout << "POS:\n";
        //     settings.printmat(pos);
        //     std::cout << "SCALE:\n";
        //     settings.printmat(scale);
        //     std::cout << "ROT:\n";
        //     settings.printmat(rot);
        //     std::cout << std::endl;
        //     std::cout << "FINAL:\n";
        //     settings.printmat(pos * rot * scale);
        //     std::cout << '\n';
        // }
            // glm::mat4 flip(
            //     glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
            //     glm::vec4(0.0f, 0.0f, -1.0f, 0.0f),
            //     glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
            //     glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
            // );
            return (pos * rot * scale);
        }

        glm::mat4 currentPos(const std::vector<KeyPosition>& positions, float time) const {
            if (positions.size() == 0)
                return glm::mat4(1.0f);
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
                return glm::mat4(1.0f);
            if (rotations.size() == 1)
                return glm::toMat4(rotations[0].rotation);
            const KeyRotation* last = &rotations[0];
            const KeyRotation* next = &rotations[1];
            for (auto i = 1; i < rotations.size() - 1; ++i){
                if (rotations[i].timestamp > time)
                    break ;
                last = &rotations[i];
                next = &rotations[i + 1];
            }
            // glm::mat4 flip(
            //     glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
            //     glm::vec4(0.0f, 0.0f, -1.0f, 0.0f),
            //     glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
            //     glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
            // );
            // return glm::toMat4(glm::slerp(last->rotation, next->rotation,
            //     getInterpolant(time, last->timestamp, next->timestamp))) * flip;
            return glm::toMat4(glm::slerp(last->rotation, next->rotation,
                getInterpolant(time, last->timestamp, next->timestamp)));
        }

        glm::mat4 currentScale(const std::vector<KeyScale>& scales, float time) const {
            if (scales.size() == 0)
                return glm::mat4(1.0f);
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
        float lastTick = 0;
        float currentTick = 0;
        std::vector<AnimTimers> _timers;
        std::vector<BoneData>   _bones;
        glm::mat4               _transformation;
		std::vector<glm::mat4>	_matrices;
};