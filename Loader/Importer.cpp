#include "Importer.hpp"

#include "debug.hpp"

MeshData process_scene(const aiScene* scene){
    if (scene->mNumMeshes != 1)
        throw(std::runtime_error("Number of meshes != 1"));
    MeshData data = process_mesh(scene->mRootNode, scene->mMeshes[0]);
    data.timers = process_animations(scene->mRootNode, scene, data.bones);
    return data;
}

MeshData importer(const char* path){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, 
		aiProcess_Triangulate
		// | aiProcess_FlipUVs
		// | aiProcess_OptimizeMeshes
		// | aiProcess_LimitBoneWeights
		// // | aiProcess_OptimizeGraph
        );
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		throw(std::runtime_error(importer.GetErrorString()));
    print_hierarchy(scene->mRootNode);
    return process_scene(scene);
}
