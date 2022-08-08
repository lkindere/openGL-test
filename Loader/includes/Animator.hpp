#pragma once

#include <vector>

#include "Bone.hpp"

#include <iostream>

#include "settings.hpp"

extern Settings settings;

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
                _matrices.push_back(glm::mat4(1.0f));
			for (auto i = 0; i < bones.size(); ++i){
                _matrices[i] = _matrices[i] * bones[i].currentMatrix(currentTime);
                //Find out why the Z changes
                // _matrices[i][3].z = 0.0f;
                for (auto j = 0; j < bones[i].children().size(); ++j){
                    _matrices[bones[i].children()[j]] = _matrices[i];
                }
				_matrices[i] = bones[i].offset() * _matrices[i];
                std::cout << "FINAL:\n";
                settings.printmat(_matrices[i]);
            }
            currentTime += 5;
            // for (auto i = 0; i < _matrices.size(); ++i){
            //     std::cout << "Matrix " << i << ":\n";
            //     settings.printmat(_matrices[i]);
            //     std::cout << std::endl;
            // }
			return _matrices;
		}

	private:
        float   maxTime = 0;
		float	currentTime = 0;
		float	previousTime = 0;
		std::vector<glm::mat4>	_matrices;
};