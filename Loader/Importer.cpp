#include "Importer.hpp"

Model process_model(const aiMesh* mesh, const aiAnimation* animation, const aiNode* root){
	VAOdata	data = process_vao(mesh);
	std::vector<Bone> bones = process_bones(mesh, animation, root);
	return Model(data, bones);
}

//Takes a path to a file, returns loaded model
Model importer(const char* path){
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
    std::cout << "N meshes: " << scene->mNumMeshes << std::endl;
    std::cout << "N anims: " << scene->mNumAnimations << std::endl;
	if (scene->mAnimations)
		return (process_model(scene->mMeshes[0], scene->mAnimations[0], scene->mRootNode));
	return (process_model(scene->mMeshes[0], nullptr, nullptr));
}
