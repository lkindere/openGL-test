#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "Importer.hpp"
#include "Converter.hpp"

#include "Debug.hpp"

std::vector<glm::vec3> process_vertices(aiMesh* mesh){
	std::vector<glm::vec3>	vertices;
	vertices.reserve(mesh->mNumVertices);
	for (auto i = 0; i < mesh->mNumVertices; ++i)
		vertices.push_back(toGLvec(mesh->mVertices[i]));
	return vertices;
}

std::vector<unsigned int> process_indices(aiMesh* mesh){
	std::vector<unsigned int>	indices;
	indices.reserve(mesh->mNumFaces * 3);
	for (auto i = 0; i < mesh->mNumFaces; ++i){
		for (auto j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
			indices.push_back(mesh->mFaces[i].mIndices[j]);
	}
	return indices;
}

std::vector<glm::vec3> process_normals(aiMesh* mesh){
	std::vector<glm::vec3>	normals;
	normals.reserve(mesh->mNumVertices);
	for (auto i = 0; i < mesh->mNumVertices; ++i)
		normals.push_back(toGLvec(mesh->mNormals[i]));
	return normals;
}

std::vector<glm::vec4> process_colors(aiMesh* mesh){
	std::vector<glm::vec4> colors;
	colors.reserve(mesh->mNumVertices);
	for (auto i = 0; i < mesh->mNumVertices; ++i)
		colors.push_back(toGLvec(mesh->mColors[0][i]));
	return colors;
}

void process_keyframes(Bone& bone, aiAnimation* animations){
	aiNodeAnim* channel = nullptr;
	for (auto i = 0; i < animations->mNumChannels; ++i){
		if (animations->mChannels[i]->mNodeName.data == bone.name){
			channel = animations->mChannels[i];
			break ;
		}
	}
	if (!channel)
		return ;
	// bone.positions.reserve(channel->mNumPositionKeys);
	for (auto j = 0; j < channel->mNumPositionKeys; ++j){
		glm::vec3 pos = toGLvec(channel->mPositionKeys[j].mValue);
		if (j > 0 && same_vec(bone.positions.rbegin()->position, pos))
			continue ;
		KeyPosition key;
		key.timestamp = channel->mPositionKeys[j].mTime;
		key.position = pos;
		bone.positions.push_back(key);
	}
	// bone.rotations.reserve(channel->mNumRotationKeys);
	for (auto j = 0; j < channel->mNumRotationKeys; ++j){
		glm::quat rot = toGLquat(channel->mRotationKeys[j].mValue);
		if (j > 0 && same_quat(bone.rotations.rbegin()->rotation, rot))
			continue ;
		KeyRotation key;
		key.timestamp = channel->mRotationKeys[j].mTime;
		key.rotation = rot;
		bone.rotations.push_back(key);
	}
	// bone.scales.reserve(channel->mNumScalingKeys);
	for (auto j = 0; j < channel->mNumScalingKeys; ++j){
		glm::vec3 scale = toGLvec(channel->mScalingKeys[j].mValue);
		if (j > 0 && same_vec(bone.scales.rbegin()->scale, scale))
			continue ;
		KeyScale key;
		key.timestamp = channel->mScalingKeys[j].mTime;
		key.scale = scale;
		bone.scales.push_back(key);
	}
}

std::vector<Bone> process_bones(aiMesh* mesh, aiAnimation* animations){
	std::vector<Bone> bones;
	if (mesh->mNumBones == 0)
		return bones;
	bones.reserve(mesh->mNumBones);
	for (auto i = 0; i < mesh->mNumBones; ++i){
		Bone bone;
		bone.ID = i;
		bone.name = mesh->mBones[i]->mName.data;
		for (auto j = 0; j < mesh->mBones[i]->mNumWeights; ++j){
			bone.weights.insert(std::make_pair(
				mesh->mBones[i]->mWeights[j].mVertexId, mesh->mBones[i]->mWeights[j].mWeight));
		}
		bone.offset = toGLmat(mesh->mBones[i]->mOffsetMatrix);
		process_keyframes(bone, animations);
		bones.push_back(bone);
	}
	return bones;
}

Model process_model(aiMesh* mesh, aiAnimation* animation){
	Model model;
	model.vertices = process_vertices(mesh);
	model.indices = process_indices(mesh);
	model.normals = process_normals(mesh);
	model.colors = process_colors(mesh);
	model.bones = process_bones(mesh, animation);
	// print_bones(model);
	return model;
}

void print_stuff(aiNode* root){
	std::cout << '\n';
	std::cout << "Node: " << root->mName.data << std::endl;
	if (root->mParent)
		std::cout << "Parent: " << root->mParent->mName.data << std::endl;
	std::cout << "Matrix:\n" 
		<< root->mTransformation.a1 << ' ' << root->mTransformation.a2 << ' ' << root->mTransformation.a3 << ' ' << root->mTransformation.a4 << '\n'
		<< root->mTransformation.b1 << ' ' << root->mTransformation.b2 << ' ' << root->mTransformation.b3 << ' ' << root->mTransformation.b4 << '\n'
		<< root->mTransformation.c1 << ' ' << root->mTransformation.c2 << ' ' << root->mTransformation.c3 << ' ' << root->mTransformation.c4 << '\n'
		<< root->mTransformation.d1 << ' ' << root->mTransformation.d2 << ' ' << root->mTransformation.d3 << ' ' << root->mTransformation.d4 << std::endl;
	std::cout << "Children: " << root->mNumChildren << std::endl;
	for (auto i = 0; i < root->mNumChildren; ++i)
		print_stuff(root->mChildren[i]);
}

std::vector<Model> importer(const char* path){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,aiProcess_Triangulate | aiProcess_FlipUVs
		| aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices | aiProcess_LimitBoneWeights
		| aiProcess_OptimizeGraph);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
		std::cout << "ASSIMP: " << importer.GetErrorString() << std::endl;
		throw(1);
	}
	print_stuff(scene->mRootNode);
	std::vector<Model>	models;
	models.reserve(scene->mNumMeshes);
	//Will need a rework with multiple meshes/animations
	(scene->mAnimations) ?
		models.push_back(process_model(scene->mMeshes[0], scene->mAnimations[0]))
		:	models.push_back(process_model(scene->mMeshes[0], nullptr));
	std::cout << "\n\n";
	return models;
}
