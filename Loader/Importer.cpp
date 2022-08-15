#include <map>
#include <vector>

#include "Importer.hpp"
#include "debug.hpp"

glm::vec3 average_position(const aiBone* bone, const aiMesh* mesh){
    std::vector<unsigned int> vertices;
    vertices.reserve(bone->mNumWeights);
    std::cout << "Bone: " << bone->mName.data << std::endl;
    for (auto i = 0; i < bone->mNumWeights; ++i)
        vertices.push_back(bone->mWeights[i].mVertexId);
    aiVector3D result;
    for (auto i = 0; i < vertices.size(); ++i)
        result += mesh->mVertices[vertices[i]];
    std::cout << "Additions\n";
    print_vec(result);
    std::cout << "Division\n";
    result /= vertices.size();
    print_vec(result);
    std::cout << "\n\n";
    return toGLvec(result);
}

std::vector<LimbData> process_limbs(const aiScene* scene, std::vector<std::string> limbs){
    std::vector<LimbData> data;
    for (auto i = 0; i < scene->mMeshes[0]->mNumBones; ++i){
        for (auto j = 0; j < limbs.size(); ++j){
            std::cout << "Comparing " << scene->mMeshes[0]->mBones[i]->mName.data << " with: " << limbs[j] << std::endl;
            if (scene->mMeshes[0]->mBones[i]->mName.data == limbs[j]){
                LimbData limb;
                limb.boneID = i;
                limb.name = limbs[j].data();
                limb.position = average_position(scene->mMeshes[0]->mBones[i], scene->mMeshes[0]);
                data.push_back(limb);
            }
        }
    }
    return data;
}

MeshData process_scene(const aiScene* scene, const std::vector<std::string>& limbs){
    if (scene->mNumMeshes != 1)
        throw(std::runtime_error("Number of meshes != 1"));
    MeshData data = process_mesh(scene->mRootNode, scene, scene->mMeshes[0]);
    data.limbs = process_limbs(scene, limbs);
    return data;
}

MeshData importer(const char* path, const std::vector<std::string>& limbs){
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
    MeshData data = process_scene(scene, limbs);
    print_hierarchy(data.nodes);
    // print_vertices(data.verts);
    return data;
}
