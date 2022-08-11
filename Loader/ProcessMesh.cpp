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

static glm::mat4 get_mesh_transform(const aiNode* node){
    std::vector<glm::mat4> matrices;
    while (node){
        matrices.push_back(toGLmat(node->mTransformation));
        node = node->mParent;
    }
    // glm::mat4 finalMat = *matrices.begin();
    // for (auto it = matrices.begin() + 1; it != matrices.end(); ++it)
    //     finalMat *= *it;
    glm::mat4 finalMat = *matrices.rbegin();
    for (auto it = matrices.rbegin() + 1; it != matrices.rend(); ++it)
        finalMat *= *it;
    std::cout << "FINAL MAT:\n" << std::endl;
    print_mat(finalMat);
    std::cout << std::endl;
    return finalMat;
}

const aiNode* find_mesh_node(const aiNode* root, unsigned int ID){
    if (root->mNumMeshes){
        for (auto i = 0; i < root->mNumMeshes; ++i){
            if (root->mMeshes[i] == ID)
                return root;
        }
    }
    for (auto i = 0; i < root->mNumChildren; ++i){
        const aiNode* ret = find_mesh_node(root->mChildren[i], ID);
        if (ret)
            return ret;
    }
    return NULL;
}

static void process_hierarchy(std::vector<BoneData>& data, const aiNode* node){
	const aiNode* current;
	for (auto i = 0; i < data.size(); ++i){
		current = node->FindNode(data[i].name.data());
		if (!current)
			throw(std::runtime_error("Node not found"));
		std::vector<unsigned short> chld;
		chld.reserve(current->mNumChildren);
		for (auto i = 0; i < current->mNumChildren; ++i){
            for (auto j = 0; j < data.size(); ++j){
                if (data[j].name == current->mChildren[i]->mName.data){
                    chld.push_back(j);
                    break ;
                }
            }
        };
        data[i].transform = toGLmat(current->mTransformation);
        data[i].children = chld;
	}
}

static std::vector<BoneData> process_bones(const aiNode* root, const aiMesh* mesh){
	std::vector<BoneData> data;
    data.reserve(mesh->mNumBones);
	for (auto i = 0; i < mesh->mNumBones; ++i){
		BoneData bone;
        bone.name = mesh->mBones[i]->mName.data;
		bone.offset = toGLmat(mesh->mBones[i]->mOffsetMatrix);
        data.push_back(bone);
	}
	process_hierarchy(data, root);
    print_bonedata(data);
	return data;
}

MeshData process_mesh(const aiNode* root, const aiMesh* mesh){
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
    //Change if more meshes than 1
    data.transformation = get_mesh_transform(find_mesh_node(root, 0));
    print_mat(data.transformation);
    data.bones = process_bones(root, mesh);
	return data;
}
