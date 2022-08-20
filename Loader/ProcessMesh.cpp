#include "ProcessMesh.hpp"
#include "debug.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static std::vector<unsigned int> process_indices(const aiMesh* mesh){
	std::vector<unsigned int>	indices;
	indices.reserve(mesh->mNumFaces * 3);
	for (auto i = 0; i < mesh->mNumFaces; ++i){
		for (auto j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
			indices.push_back(mesh->mFaces[i].mIndices[j]);
	}
	return indices;
}

static void process_weights(const aiMesh* mesh, Vert& vert, int index){
	int		counter = 0;
	int		matches[3] = {0};
	float	weights[3] = {0};
	for (auto i = 0; i < mesh->mNumBones; ++i){
		for (auto j = 0; j < mesh->mBones[i]->mNumWeights; ++j){
			if (mesh->mBones[i]->mWeights[j].mVertexId == index){
				if (counter >= 3)
					throw(std::runtime_error("Too many bones per vertex"));
				matches[counter] = i;
				weights[counter] = mesh->mBones[i]->mWeights[j].mWeight;
				++counter;
				break ;	//Prevents duplicates that assimp imports for some reason
			}
		}
	}
	vert.bones = glm::ivec3(matches[0], matches[1], matches[2]);
	vert.weights = glm::vec3(weights[0], weights[1], weights[2]);
}

static std::vector<Vert> process_verts(const aiMesh* mesh){
    std::vector<Vert> data;
	for (auto i = 0; i < mesh->mNumVertices; ++i){
		Vert vert;
		vert.vertices = toGLvec(mesh->mVertices[i]);
		vert.normals = toGLvec(mesh->mNormals[i]);
        mesh->HasVertexColors(0) ?  //No need for colors in the future if everything is rexturized
		    vert.colors = toGLvec(mesh->mColors[0][i])
            :   vert.colors = glm::vec4(1.0f);
        vert.textures = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        process_weights(mesh, vert, i);
		data.push_back(vert);
	}
    return data;
}

static std::vector<KeyPosition> process_positions(aiNodeAnim* node){
    // std::cout << "N positions: " << node->mNumPositionKeys << std::endl;
	std::vector<KeyPosition> positions;
	for (auto i = 0; i < node->mNumPositionKeys; ++i){
		KeyPosition pos;
		pos.position = toGLvec(node->mPositionKeys[i].mValue);
		pos.timestamp = node->mPositionKeys[i].mTime;
		positions.push_back(pos);
	}
	return positions;
}

static std::vector<KeyRotation> process_rotations(aiNodeAnim* node){
    // std::cout << "N rotations: " << node->mNumRotationKeys << std::endl;
	std::vector<KeyRotation> rotations;
	for (auto i = 0; i < node->mNumRotationKeys; ++i){
		KeyRotation rot;
		rot.rotation = toGLquat(node->mRotationKeys[i].mValue);
		rot.timestamp = node->mRotationKeys[i].mTime;
		rotations.push_back(rot);
	}
	return rotations;
}

static std::vector<KeyScale> process_scales(aiNodeAnim* node){
    // std::cout << "N scales: " << node->mNumScalingKeys << std::endl;
	std::vector<KeyScale> scales;
	for (auto i = 0; i < node->mNumScalingKeys; ++i){
		KeyScale scl;
		scl.scale = toGLvec(node->mScalingKeys[i].mValue);
		scl.timestamp = node->mScalingKeys[i].mTime;
		scales.push_back(scl);
	}
	return scales;
}

static std::vector<AnimData> process_animations(const aiNode* node, const aiScene* scene){
    std::vector<AnimData> animations;
    if (scene->mNumAnimations == 0)
        return animations;
    animations.reserve(scene->mNumAnimations);
    for (auto i = 0; i < scene->mNumAnimations; ++i){
        animations.push_back(AnimData());
        for (auto j = 0; j < scene->mAnimations[i]->mNumChannels; ++j){
            if (scene->mAnimations[i]->mChannels[j]->mNodeName == node->mName){
                animations[i].positions = process_positions(scene->mAnimations[i]->mChannels[j]);
                animations[i].rotations = process_rotations(scene->mAnimations[i]->mChannels[j]);
                animations[i].scales = process_scales(scene->mAnimations[i]->mChannels[j]);
                break ;
            }
        }
    }
    return animations;
}

std::unique_ptr<glm::vec3> process_position(const aiBone* bone, const aiMesh* mesh,
    const std::vector<std::string>& locateBones)
{
    if (std::find(locateBones.begin(), locateBones.end(), bone->mName.data) == locateBones.end())
        return nullptr;
    std::vector<unsigned int> vertices;
    vertices.reserve(bone->mNumWeights);
    std::cout << "Bone: " << bone->mName.data << std::endl;
    for (auto i = 0; i < bone->mNumWeights; ++i)
        vertices.push_back(bone->mWeights[i].mVertexId);
    aiVector3D result;
    for (auto i = 0; i < vertices.size(); ++i)
        result += mesh->mVertices[vertices[i]];
    result /= vertices.size();
    return std::unique_ptr<glm::vec3>(new glm::vec3(toGLvec(result)));
}

static std::unique_ptr<BoneData> process_bone(const aiNode* node, const aiScene* scene, const aiMesh* mesh,
    const LoadingParameters& parameters)
{
    for (auto i = 0; i < mesh->mNumBones; ++i){
        if (mesh->mBones[i]->mName == node->mName){
            std::cout << "Bone: " << node->mName.data << " ID: " << i << std::endl;
            std::unique_ptr<BoneData> bone(new BoneData());
            bone->ID = i;
            bone->offset = toGLmat(mesh->mBones[i]->mOffsetMatrix);
            bone->animations = process_animations(node, scene);
            bone->position = process_position(mesh->mBones[i], mesh, parameters.locateBones);
            return bone;
        }
    }
    return nullptr;
}

static void recursive_nodes(NodeData& node, const aiNode* root, const aiScene* scene, const aiMesh* mesh,
    const LoadingParameters& parameters)
{
    node.name = root->mName.data;
    node.bone = process_bone(root, scene, mesh, parameters);
    node.transformation = toGLmat(root->mTransformation);
    node.children.resize(root->mNumChildren);
    for (auto i = 0; i < root->mNumChildren; ++i)
        recursive_nodes(node.children[i], root->mChildren[i], scene, mesh, parameters);
}

static NodeData process_nodes(const aiScene* scene, const aiMesh* mesh,
    const LoadingParameters& parameters)
{
    NodeData nodes;
    recursive_nodes(nodes, scene->mRootNode, scene, mesh, parameters);
    return nodes;
}

std::vector<AnimTimers> process_timers(const aiScene* scene){
    std::vector<AnimTimers> timers;
    timers.reserve(scene->mNumAnimations);
    for (auto i = 0; i < scene->mNumAnimations; ++i){
        AnimTimers anim;
        anim.duration = scene->mAnimations[i]->mDuration;
        anim.tps = scene->mAnimations[i]->mTicksPerSecond;
        timers.push_back(anim);
    }
    return timers;
}

TextureData process_textures(const aiScene* scene){
    TextureData data;
    std::cout << "Has textures: " << scene->HasTextures() << std::endl;
    if (!scene->HasTextures()){
        data.data = nullptr;
        return data;
    }
    data.data = stbi_load_from_memory((unsigned char*)scene->mTextures[0]->pcData, scene->mTextures[0]->mWidth,
        &data.width, &data.height, &data.channels, 0);
    return data;
}

HitboxData process_hitbox(const aiScene* scene){
    if (scene->mNumMeshes < 2)
        return HitboxData();
    const aiMesh* mesh = scene->mMeshes[1];
    HitboxData data;
    data.min = toGLvec(mesh->mVertices[0]);
    data.max = toGLvec(mesh->mVertices[0]);
    for (auto i = 1; i < mesh->mNumVertices; ++i){
        if (mesh->mVertices[i].x < data.min.x)
            data.min.x = mesh->mVertices[i].x;
        else if (mesh->mVertices[i].x > data.max.x)
            data.max.x = mesh->mVertices[i].x;
        if (mesh->mVertices[i].y < data.min.y)
            data.min.y = mesh->mVertices[i].y;
        else if (mesh->mVertices[i].y > data.max.y)
            data.max.y = mesh->mVertices[i].y;
        if (mesh->mVertices[i].z < data.min.z)
            data.min.z = mesh->mVertices[i].z;
        else if (mesh->mVertices[i].z > data.max.z)
            data.max.z = mesh->mVertices[i].z;
    }
    return data;
}

MeshData process_mesh(const aiScene* scene, const LoadingParameters& parameters){
    const aiMesh* mesh = scene->mMeshes[0];

	MeshData    data;
	data.indices = process_indices(mesh);
    data.verts = process_verts(mesh);
    data.texture = process_textures(scene);
    data.timers = process_timers(scene);
    data.nodes = process_nodes(scene, mesh, parameters);
    data.hitbox = process_hitbox(scene);
	return data;
}
