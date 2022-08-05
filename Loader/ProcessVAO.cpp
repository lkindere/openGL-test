#include "ProcessVAO.hpp"

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
	colors.reserve(mesh->mNumVertices);
	for (auto i = 0; i < mesh->mNumVertices; ++i)
		colors.push_back(toGLvec(mesh->mColors[0][i]));
	return colors;
}

static void process_bones(const aiMesh* mesh, Vert& vert, int index){
	int		counter = 0;
	int		matches[3] = {0};
	float	weights[3] = {0.0f};
	for (auto i = 0; i < mesh->mNumBones; ++i){
		for (auto j = 0; j < mesh->mBones[i]->mNumWeights; ++j){
			if (mesh->mBones[i]->mWeights[j].mVertexId == index){
				if (counter >= 3)
					throw(std::runtime_error("Too many bones per vertex"));
				matches[counter] = j;
				weights[counter] = mesh->mBones[i]->mWeights[j].mWeight;
				++counter;
				break ;	//Prevents duplicates that assimp imports for some reason
			}
		}
	}
	vert.bones = glm::ivec3(matches[0], matches[1], matches[2]);
	vert.weights = glm::vec3(weights[0], weights[1], weights[2]);
}

VAOdata	process_vao(const aiMesh* mesh){
	VAOdata	data;
	data.indices = process_indices(mesh);
	std::vector<glm::vec3>	vertices = process_vertices(mesh);
	std::vector<glm::vec3>	normals = process_normals(mesh);
	std::vector<glm::vec4>	colors = process_colors(mesh);
	for (auto i = 0; i < vertices.size(); ++i){
		Vert vert;
		vert.vertices = vertices[i];
		vert.normals = normals[i];
		vert.colors = colors[i];
		process_bones(mesh, vert, i);
		data.verts.push_back(vert);
	}
	return data;
}
