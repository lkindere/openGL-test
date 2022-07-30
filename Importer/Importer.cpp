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

Model process_model(aiMesh* mesh){
	Model model;
	model.vertices = process_vertices(mesh);
	model.indices = process_indices(mesh);
	model.normals = process_normals(mesh);;
	return model;
}

std::vector<Model> importer(const char* path){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs );
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
		std::cout << "ASSIMP: " << importer.GetErrorString() << std::endl;
		throw(1);
	}
#ifdef DEBUG
	std::cout << "Meshes: " << scene->mNumMeshes << '\n' << std::endl;
#endif
	std::vector<Model>	models;
	models.reserve(scene->mNumMeshes);
	for (auto i = 0; i < scene->mNumMeshes; ++i)
		models.push_back(process_model(scene->mMeshes[i]));
	return models;
}
