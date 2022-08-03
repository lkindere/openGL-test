#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "Importer.hpp"

std::vector<glm::vec3> process_vertices(aiMesh* mesh){
	std::vector<glm::vec3>	vertices;
#ifdef DEBUG
	std::cout << "\nNumber of vertices: " << mesh->mNumVertices << '\n' << std::endl;
#endif
	vertices.reserve(mesh->mNumVertices);
	for (auto i = 0; i < mesh->mNumVertices; ++i){
	vertices.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
	}
	return vertices;
}

//Will not be valid for anything other than triangles
//Undefined without aiProcess_Triangulate flag
//Most likely will crash if faces == 0
std::vector<unsigned int> process_indices(aiMesh* mesh){
	std::vector<unsigned int>	indices;
#ifdef DEBUG
	std::cout << "\nNumber of indices: " << mesh->mNumFaces * mesh->mFaces[0].mNumIndices << '\n' << std::endl;
#endif
	indices.reserve(mesh->mNumFaces * mesh->mFaces[0].mNumIndices);
	for (auto i = 0; i < mesh->mNumFaces; ++i){
		for (auto j = 0; j < mesh->mFaces[i].mNumIndices; ++j){
			indices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}
	return indices;
}

std::vector<glm::vec3> process_normals(aiMesh* mesh){
	std::vector<glm::vec3>	normals;
	normals.reserve(mesh->mNumVertices);
	for (auto i = 0; i < mesh->mNumVertices; ++i){
		normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
	}
	return normals;
}

std::vector<glm::vec4> process_colors(aiMesh* mesh){
	std::vector<glm::vec4> colors;
	colors.reserve(mesh->mNumVertices);
	for (auto i = 0; i < mesh->mNumVertices; ++i)
		colors.push_back(glm::vec4(mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b, mesh->mColors[0][i].a));
	return colors;
}

//Not sure if correct
glm::mat4	convert_matrix(const aiMatrix4x4& aiMatrix){
	glm::vec4 v1(aiMatrix.a1, aiMatrix.a2, aiMatrix.a3, aiMatrix.a4);
	glm::vec4 v2(aiMatrix.b1, aiMatrix.b2, aiMatrix.b3, aiMatrix.b4);
	glm::vec4 v3(aiMatrix.c1, aiMatrix.c2, aiMatrix.c3, aiMatrix.c4);
	glm::vec4 v4(aiMatrix.d1, aiMatrix.d2, aiMatrix.d3, aiMatrix.d4);
	return (glm::mat4(v1, v2, v3, v4));
}

std::vector<Bone> process_bones(aiMesh* mesh){
	std::vector<Bone> bones;
	bones.reserve(mesh->mNumBones);
	for (auto i = 0; i < mesh->mNumBones; ++i){
		Bone bone;
		std::cout << "N weights: " << mesh->mBones[i]->mNumWeights << std::endl;
		for (auto j = 0; j < mesh->mBones[i]->mNumWeights; ++j){
			// if (j == MAX_WEIGHTS){
			// 	std::cout << "More weights detected per bone than defined" << std::endl;
			// 	break ;
			// }
			std::cout << "Bone: " << i << " Affecting: " << mesh->mBones[i]->mWeights[j].mVertexId << ' ' << mesh->mBones[i]->mWeights[j].mWeight << std::endl;
			bone.vertices[j] = mesh->mBones[i]->mWeights[j].mVertexId;
			bone.weights[j] = mesh->mBones[i]->mWeights[j].mWeight;
		}
		bone.offset = convert_matrix(mesh->mBones[i]->mOffsetMatrix);
		bone.ID = i;
		bones.push_back(bone);
	}
	// exit (0);
	return bones;
}

Model process_model(aiMesh* mesh){
	Model model;
	model.vertices = process_vertices(mesh);
	model.indices = process_indices(mesh);
	model.normals = process_normals(mesh);
	model.colors = process_colors(mesh);
	// model.bones = process_bones(mesh);
	return model;
}

std::vector<Model> importer(const char* path){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,aiProcess_Triangulate | aiProcess_FlipUVs
		| aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices | aiProcess_LimitBoneWeights);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
		std::cout << "ASSIMP: " << importer.GetErrorString() << std::endl;
		throw(1);
	}
	std::cout << "N meshes: " << scene->mNumMeshes << std::endl;
	std::cout << AI_MAX_BONE_WEIGHTS << std::endl;
	std::vector<Model>	models;
	models.reserve(scene->mNumMeshes);
	for (auto i = 0; i < scene->mNumMeshes; ++i)
		models.push_back(process_model(scene->mMeshes[i]));
	std::cout << "\n\n";
	return models;
}
