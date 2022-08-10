#include "ProcessAnimations.hpp"

#include "debug.hpp"

static std::vector<KeyPosition> process_positions(aiNodeAnim* node){
	std::vector<KeyPosition> positions;
    //  std::cout << "nPosition keys: " << node->mNumPositionKeys << std::endl;
	for (auto i = 0; i < node->mNumPositionKeys; ++i){
		KeyPosition pos;
		pos.position = toGLvec(node->mPositionKeys[i].mValue);
		// if (i > 0 && same_vec(pos.position, positions.rbegin()->position))
		// 	continue ;  //Could be bad for interpolating unless next is also the same
        //Keep only first and last in such cases
		pos.timestamp = node->mPositionKeys[i].mTime;
		positions.push_back(pos);
	}
	return positions;
}

static std::vector<KeyRotation> process_rotations(aiNodeAnim* node){
	std::vector<KeyRotation> rotations;
        // std::cout << "nRotation keys: " << node->mNumRotationKeys << std::endl;
	for (auto i = 0; i < node->mNumRotationKeys; ++i){
		KeyRotation rot;
		rot.rotation = toGLquat(node->mRotationKeys[i].mValue);
		// if (i > 0 && same_quat(rot.rotation, rotations.rbegin()->rotation))
		// 	continue ;
		rot.timestamp = node->mRotationKeys[i].mTime;
		rotations.push_back(rot);
	}
	return rotations;
}

static std::vector<KeyScale> process_scales(aiNodeAnim* node){
	std::vector<KeyScale> scales;
    // std::cout << "nScaling keys: " << node->mNumScalingKeys << std::endl;
	for (auto i = 0; i < node->mNumScalingKeys; ++i){
		KeyScale scl;
		scl.scale = toGLvec(node->mScalingKeys[i].mValue);
		// if (i > 0 && same_vec(scl.scale, scales.rbegin()->scale))
		// 	continue ;
		scl.timestamp = node->mScalingKeys[i].mTime;
		scales.push_back(scl);
	}
	return scales;
}

std::vector<AnimTimers> process_animations(const aiNode* root, const aiScene* scene, std::vector<BoneData>& bones){
    std::vector<AnimTimers> timers;
    if (scene->mNumAnimations == 0)
        return timers;
    for (auto i = 0; i < scene->mNumAnimations; ++i){
        for (auto j = 0; j < scene->mAnimations[i]->mNumChannels; ++j){
            for (auto k = 0; k < bones.size(); ++k){
                if (bones[k].name == scene->mAnimations[i]->mChannels[j]->mNodeName.data){
                    AnimData temp;
                    temp.positions = process_positions(scene->mAnimations[i]->mChannels[j]);
                    temp.rotations = process_rotations(scene->mAnimations[i]->mChannels[j]);
                    temp.scales = process_scales(scene->mAnimations[i]->mChannels[j]);
                    bones[k].animations.push_back(temp);
                    break ;
                }
            }
        }
        AnimTimers time;
        time.duration = scene->mAnimations[i]->mDuration;
        time.tps = scene->mAnimations[i]->mTicksPerSecond;
        timers.push_back(time);
    }
    print_bonedata(bones);
    return timers;
}