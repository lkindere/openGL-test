#include "ProcessBones.hpp"

static std::vector<KeyPosition> process_positions(aiNodeAnim* node){
	std::vector<KeyPosition> positions;
	for (auto i = 0; i < node->mNumPositionKeys; ++i){
		KeyPosition pos;
		pos.timestamp = node->mPositionKeys[i].mTime;
		pos.position = toGLvec(node->mPositionKeys[i].mValue);
		positions.push_back(pos);
	}
	return positions;
}

static std::vector<KeyRotation> process_rotations(aiNodeAnim* node){
	std::vector<KeyRotation> rotations;
	for (auto i = 0; i < node->mNumRotationKeys; ++i){
		KeyRotation rot;
		rot.timestamp = node->mRotationKeys[i].mTime;
		rot.rotation = toGLquat(node->mRotationKeys[i].mValue);
		rotations.push_back(rot);
	}
	return rotations;
}

static std::vector<KeyScale> process_scales(aiNodeAnim* node){
	std::vector<KeyScale> scales;
	for (auto i = 0; i < node->mNumScalingKeys; ++i){
		KeyScale scl;
		scl.timestamp = node->mScalingKeys[i].mTime;
		scl.scale = toGLvec(node->mScalingKeys[i].mValue);
		scales.push_back(scl);
	}
	return scales;
}

static unsigned short find_boneID(const std::vector<Bone>& data, const std::string& name){
	for (auto it = data.begin(); it != data.end(); ++it){
		if (it->name() == name)
			return it->ID();
	}
	throw(std::runtime_error("Bone ID not found\n"));
}

static void process_hierarchy(std::vector<Bone>& data, const aiNode* node){
	const aiNode* current;
	for (auto it = data.begin(); it != data.end(); ++it){
		current = node->FindNode(it->name().data());
		if (!current)
			continue ;
		std::vector<unsigned short> chld;
		chld.reserve(current->mNumChildren);
		for (auto i = 0; i < current->mNumChildren; ++i)
			chld.push_back(find_boneID(data, current->mChildren[i]->mName.data));
		it->setRelative(toGLmat(current->mTransformation));
		it->setChildren(chld);
	}
}

std::vector<Bone> process_bones(const aiMesh* mesh, const aiAnimation* animation, const aiNode* root){
	std::vector<Bone> data;
	if (!animation)
		return data;
	for (auto i = 0; i < mesh->mNumBones; ++i){
		Bone bone(mesh->mBones[i]->mName.data);
		bone.setID(i);
		bone.setOffset(toGLmat(mesh->mBones[i]->mOffsetMatrix));
		for (auto j = 0; j < animation->mNumChannels; ++j){
			if (bone.name() == animation->mChannels[j]->mNodeName.data){
				bone.setPositions(process_positions(animation->mChannels[j]));
				bone.setRotations(process_rotations(animation->mChannels[j]));
				bone.setScales(process_scales(animation->mChannels[j]));
				data.push_back(bone);
				break ;
			}
		}
	}
	process_hierarchy(data, root);
	return data;
}
