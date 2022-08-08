#include "ProcessBones.hpp"

#include <iostream>


#include "settings.hpp"

extern Settings settings;

static std::vector<KeyPosition> process_positions(aiNodeAnim* node){
	std::vector<KeyPosition> positions;
     std::cout << "nPosition keys: " << node->mNumPositionKeys << std::endl;
	for (auto i = 0; i < node->mNumPositionKeys; ++i){
		KeyPosition pos;
		pos.position = toGLvec(node->mPositionKeys[i].mValue);
        std::cout << "Pos: " << pos.position.x << ' '
         << pos.position.y << ' '
          << pos.position.z << std::endl;
		if (i > 0 && same_vec(pos.position, positions.rbegin()->position))
			continue ;
		pos.timestamp = node->mPositionKeys[i].mTime;
		positions.push_back(pos);
	}
    for (auto i = 0; i < positions.size(); ++i)
        std::cout << "Position: " << positions[i].position.x << ' '
            << positions[i].position.y << ' '
            << positions[i].position.z << std::endl;
	return positions;
}

static std::vector<KeyRotation> process_rotations(aiNodeAnim* node){
	std::vector<KeyRotation> rotations;
        std::cout << "nRotation keys: " << node->mNumRotationKeys << std::endl;
	for (auto i = 0; i < node->mNumRotationKeys; ++i){
		KeyRotation rot;
		rot.rotation = toGLquat(node->mRotationKeys[i].mValue);
		if (i > 0 && same_quat(rot.rotation, rotations.rbegin()->rotation))
			continue ;
		rot.timestamp = node->mRotationKeys[i].mTime;
		rotations.push_back(rot);
	}
	return rotations;
}

static std::vector<KeyScale> process_scales(aiNodeAnim* node){
	std::vector<KeyScale> scales;
    std::cout << "nScaling keys: " << node->mNumScalingKeys << std::endl;
	for (auto i = 0; i < node->mNumScalingKeys; ++i){
		KeyScale scl;
		scl.scale = toGLvec(node->mScalingKeys[i].mValue);
		if (i > 0 && same_vec(scl.scale, scales.rbegin()->scale))
			continue ;
		scl.timestamp = node->mScalingKeys[i].mTime;
		scales.push_back(scl);
	}
	return scales;
}

static unsigned short find_boneID(const std::vector<Bone>& data, const std::string& name){
	for (auto it = data.begin(); it != data.end(); ++it){
		if (it->name() == name)
			return it->ID();
	}
    std::cout << "Bone: " << name << std::endl;
    std::cout << "All:\n";
    for (auto i = 0; i < data.size(); ++i){
        std::cout << data[i].name() << std::endl;
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
    for (auto i = 0; i < root->mNumChildren; ++i){
        std::cout << "Name: " << root->mChildren[i]->mName.data << std::endl;
        std::cout << "Transformation:\n";
        settings.printmat(toGLmat(root->mChildren[i]->mTransformation));
        std::cout << '\n';
    }
    root = root->mChildren[0];
    for (auto i = 0; i < root->mNumChildren; ++i){
        std::cout << "Name: " << root->mChildren[i]->mName.data << std::endl;
        std::cout << "Transformation:\n";
        settings.printmat(toGLmat(root->mChildren[i]->mTransformation));
        std::cout << '\n';
    }
    exit(0);
    std::cout << "Num bones: " << mesh->mNumBones << std::endl;
    for (auto i = 0; i < mesh->mNumBones; ++i)
        std::cout << "Bone name: " << mesh->mBones[i]->mName.data << std::endl;
    std::cout << '\n';
    std::cout << "Animation nChannels: " << animation->mNumChannels << '\n' << std::endl;
    for (auto i = 0; i < animation->mNumChannels; ++i)
        std::cout << "Anim name: " << animation->mChannels[i]->mNodeName.data << std::endl;
    std::cout << '\n';
	for (auto i = 0; i < mesh->mNumBones; ++i){
		Bone bone(mesh->mBones[i]->mName.data);
		bone.setID(i);
		bone.setOffset(toGLmat(mesh->mBones[i]->mOffsetMatrix));
		for (auto j = 0; j < animation->mNumChannels; ++j){
            std::cout << "Bone name: " << bone.name() << " - " << "Node name: " << animation->mChannels[j]->mNodeName.data << std::endl;
			if (bone.name() == animation->mChannels[j]->mNodeName.data){
                std::cout << "MATCH" << std::endl;
				bone.setPositions(process_positions(animation->mChannels[j]));
				bone.setRotations(process_rotations(animation->mChannels[j]));
				bone.setScales(process_scales(animation->mChannels[j]));
				data.push_back(bone);
				break ;
			}
		}
	}
    std::cout << "\n\n";
	process_hierarchy(data, root);
	return data;
}
