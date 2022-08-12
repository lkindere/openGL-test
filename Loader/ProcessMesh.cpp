#include "ProcessMesh.hpp"
#include "debug.hpp"

static std::vector<unsigned int> process_indices(const aiMesh* mesh){
	std::vector<unsigned int>	indices;
	indices.reserve(mesh->mNumFaces * 3);
	for (auto i = 0; i < mesh->mNumFaces; ++i){
		for (auto j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
			indices.push_back(mesh->mFaces[i].mIndices[j]);
	}
	return indices;
}

static std::vector<glm::vec3> process_vertices(const aiMesh* mesh){
	std::vector<glm::vec3>	vertices;
	vertices.reserve(mesh->mNumVertices);
	for (auto i = 0; i < mesh->mNumVertices; ++i)
		vertices.push_back(toGLvec(mesh->mVertices[i]));
	return vertices;
}

static std::vector<glm::vec3> process_normals(const aiMesh* mesh){
	std::vector<glm::vec3>	normals;
	normals.reserve(mesh->mNumVertices);
	for (auto i = 0; i < mesh->mNumVertices; ++i)
		normals.push_back(toGLvec(mesh->mNormals[i]));
	return normals;
}

static std::vector<glm::vec4> process_colors(const aiMesh* mesh){
	std::vector<glm::vec4> colors;
    if (!mesh->mColors[0])
        return colors;
	colors.reserve(mesh->mNumVertices);
	for (auto i = 0; i < mesh->mNumVertices; ++i)
		colors.push_back(toGLvec(mesh->mColors[0][i]));
	return colors;
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

static std::vector<KeyPosition> process_positions(aiNodeAnim* node){
	std::vector<KeyPosition> positions;
     std::cout << "nPosition keys: " << node->mNumPositionKeys << std::endl;
	for (auto i = 0; i < node->mNumPositionKeys; ++i){
		KeyPosition pos;
		pos.position = toGLvec(node->mPositionKeys[i].mValue);
		// if (i > 0 && same_vec(pos.position, positions.rbegin()->position))
		// 	continue ;  //Could be bad for interpolating unless next is also the same
        //Keep only first and last in such cases
		pos.timestamp = node->mPositionKeys[i].mTime;
		positions.push_back(pos);
	}
	return positions;
}

static std::vector<KeyRotation> process_rotations(aiNodeAnim* node){
	std::vector<KeyRotation> rotations;
        std::cout << "nRotation keys: " << node->mNumRotationKeys << std::endl;
	for (auto i = 0; i < node->mNumRotationKeys; ++i){
		KeyRotation rot;
		rot.rotation = toGLquat(node->mRotationKeys[i].mValue);
		// if (i > 0 && same_quat(rot.rotation, rotations.rbegin()->rotation))
		// 	continue ;
		rot.timestamp = node->mRotationKeys[i].mTime;
		rotations.push_back(rot);
	}
	return rotations;
}

static std::vector<KeyScale> process_scales(aiNodeAnim* node){
	std::vector<KeyScale> scales;
    std::cout << "nScaling keys: " << node->mNumScalingKeys << std::endl;
	for (auto i = 0; i < node->mNumScalingKeys; ++i){
		KeyScale scl;
		scl.scale = toGLvec(node->mScalingKeys[i].mValue);
		// if (i > 0 && same_vec(scl.scale, scales.rbegin()->scale))
		// 	continue ;
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

static BoneData* process_bone(const aiNode* node, const aiScene* scene, const aiMesh* mesh){
    for (auto i = 0; i < mesh->mNumBones; ++i){
        if (mesh->mBones[i]->mName == node->mName){
            BoneData* bone = new BoneData;
            bone->ID = i;
            bone->offset = toGLmat(mesh->mBones[i]->mOffsetMatrix);
            bone->animations = process_animations(node, scene);
            return bone;
        }
    }
    return nullptr;
}

static void process_nodes(NodeData& node, const aiNode* root, const aiScene* scene, const aiMesh* mesh){
    node.name = root->mName.data;
    node.bone = process_bone(root, scene, mesh);
    node.transformation = toGLmat(root->mTransformation);
    node.children.resize(root->mNumChildren);
    for (auto i = 0; i < root->mNumChildren; ++i)
        process_nodes(node.children[i], root->mChildren[i], scene, mesh);

//     data.reserve(mesh->mNumBones);
// 	for (auto i = 0; i < mesh->mNumBones; ++i){
// 		BoneData bone;
//         bone.name = mesh->mBones[i]->mName.data;
// 		bone.offset = toGLmat(mesh->mBones[i]->mOffsetMatrix);
//         data.push_back(bone);
// 	}
// 	process_hierarchy(data, root);
//     print_bonedata(data);
// 	return data;
}

MeshData process_mesh(const aiNode* root, const aiScene* scene, const aiMesh* mesh){
	MeshData    data;
	data.indices = process_indices(mesh);
	std::vector<glm::vec3>	vertices = process_vertices(mesh);
	std::vector<glm::vec3>	normals = process_normals(mesh);
	std::vector<glm::vec4>	colors = process_colors(mesh);
	for (auto i = 0; i < vertices.size(); ++i){
		Vert vert;
		vert.vertices = vertices[i];
		vert.normals = normals[i];
        (colors.size() != 0) ?
		    vert.colors = colors[i] : vert.colors = glm::vec4(1.0f);
        process_weights(mesh, vert, i);
		data.verts.push_back(vert);
	}
    process_nodes(data.nodes, root, scene, mesh);
	return data;
}
