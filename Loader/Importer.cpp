#include "ProcessMesh.hpp"
#include "Importer.hpp"
#include "ldebug.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

MeshData process_scene(const aiScene* scene){
    // if (scene->mNumMeshes != 1)
    //     throw(std::runtime_error("Number of meshes != 1"));
    MeshData data = process_mesh(scene);
    return data;
}

MeshData importer(const char* path){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, 
		aiProcess_Triangulate
		// | aiProcess_FlipUVs
		| aiProcess_OptimizeMeshes
		// | aiProcess_LimitBoneWeights
		// | aiProcess_OptimizeGraph
        );
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		throw(std::runtime_error(importer.GetErrorString()));
    MeshData data = process_scene(scene);
    // print_hierarchy(data.nodes);
    // print_vertices(data.verts);
    std::cout << "Loaded " << path << " successfully\n";
    return data;
}
