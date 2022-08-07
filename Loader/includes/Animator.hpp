#pragma once

#include <vector>

#include "Bone.hpp"

#include <iostream>

class Animator
{
	public:
		Animator() {}

		void init(const std::vector<Bone>& bones) {
			_matrices.reserve(bones.size());
            for (auto i = 0; i < bones.size(); ++i){
                if (bones[i].positions().rbegin()->timestamp > maxTime)
                    maxTime = bones[i].positions().rbegin()->timestamp;
                if (bones[i].rotations().rbegin()->timestamp > maxTime)
                    maxTime = bones[i].rotations().rbegin()->timestamp;
                if (bones[i].scales().rbegin()->timestamp > maxTime)
                    maxTime = bones[i].scales().rbegin()->timestamp;
            }
            std::cout << "maxTime: " << maxTime << std::endl;
		}
		
		const std::vector<glm::mat4>& updateMatrices(const std::vector<Bone>& bones){
			if (currentTime > maxTime)
                currentTime = 0;
            _matrices.clear();
			for (auto i = 0; i < bones.size(); ++i)
				_matrices.push_back(bones[i].currentMatrix(currentTime));
            currentTime += 5;
			return _matrices;
		}

	private:
        float   maxTime = 0;
		float	currentTime = 0;
		float	previousTime = 0;
		std::vector<glm::mat4>	_matrices;
};