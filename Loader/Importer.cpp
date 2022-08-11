#include "Importer.hpp"

#include "debug.hpp"

MeshData process_scene(const aiScene* scene){
    if (scene->mNumMeshes != 1)
        throw(std::runtime_error("Number of meshes != 1"));
    MeshData data = process_mesh(scene->mRootNode, scene->mMeshes[0]);
    data.inverse = toGLmat(scene->mRootNode->mTransformation.Inverse());
    data.timers = process_animations(scene->mRootNode, scene, data.bones);
    // if (data.bones.size() != 0){
    //     for (int i = 0; i < data.bones[0].animations.size(); ++i){
    //         print_keyframes(data.bones[0].animations[0].positions);
    //         print_keyframes(data.bones[0].animations[0].rotations);
    //         print_keyframes(data.bones[0].animations[0].scales);
    //     }
    // }
    std::cout << "Base transform:\n";
    print_mat(data.transformation);
    std::cout << std::endl;
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
    if (scene->mNumAnimations != 0){
        std::cout << "Channels:\n";
        for (auto i = 0; i < scene->mAnimations[0]->mNumChannels; ++i)
            std::cout << scene->mAnimations[0]->mChannels[i]->mNodeName.data << '\n';
        std::cout << std::endl;
    }
    return process_scene(scene);
}
