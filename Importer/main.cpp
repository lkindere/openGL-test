#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include <vector>

int main(void)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("../untitled.obj", aiProcess_Triangulate | aiProcess_FlipUVs );
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
		std::cout << "ASSIMP: " << importer.GetErrorString() << 'n';
		throw(1);
	}
	std::cout << "Meshes: " << scene->mNumMeshes << std::endl;
	aiMesh *mesh = scene->mMeshes[0];
	std::cout << "Vertices: " << mesh->mNumVertices << std::endl;
	for (int i = 0; i < mesh->mNumVertices; ++i){
		std::cout << "Vertice " << i << ": " << "X: " << mesh->mVertices[i].x << "Y: " << mesh->mVertices[i].y << "Z: " << mesh->mVertices[i].z << std::endl;
	}
	// vertice.
}
