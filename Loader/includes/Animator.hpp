#pragma once

#include <vector>

#include "Bone.hpp"

class Animator
{
	public:
		Animator() {}

		void reserve(size_t size) {
			_matrices.reserve(size);
		}
		
		const std::vector<glm::mat4>& updateMatrices(const std::vector<Bone>& bones){
			_matrices.clear();
			for (auto i = 0; i < bones.size(); ++i)
				_matrices.push_back(bones[i].currentMatrix(currentTime));
			return _matrices;
		}

	private:
		float	currentTime = 0;
		float	previousTime = 0;
		std::vector<glm::mat4>	_matrices;
};