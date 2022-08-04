#pragma once

#include <vector>

#include <glad/gl.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "Importer.hpp"

//Vertice
//Normal
//Color
//Bones affecting the vertice
//Weights per bone
struct Vert
{
	glm::vec3	vertices;
	glm::vec3	normals;
	glm::vec4	colors;
	glm::ivec3	bones;
	glm::vec3	weights;
};

struct Mesh
{
	std::vector<Vert>	vertices;
	std::vector<GLuint>	indices;
	std::vector<Bone>	bones;
};

//Indexes start from 1
void check_bones(Vert& vert, unsigned int index, const std::vector<Bone>& bones){
	int				matches[MAX_WEIGHTS] = {-1};
	float			weights[MAX_WEIGHTS] = {0.0f};
	unsigned int	counter = 0;
	for (auto i = 0; i < bones.size(); ++i){
		if (bones[i].weights.find(index) != bones[i].weights.end()){
			matches[counter] = i;
			weights[counter] = bones[i].weights.find(index)->second;
			++counter;
		}
	}
#ifdef DEBUG
	if (counter > MAX_WEIGHTS)
		std::cout << "Too many bone matches per vertex while loading\n" << std::endl;
#endif
	vert.bones = glm::ivec3(matches[0], matches[1], matches[2]);
	vert.weights = glm::vec3(weights[0], weights[1], weights[2]);
}

Mesh load_mesh(const char* path){
#ifdef DEBUG
	std::cout << "Loading: " << path << std::endl;
#endif
	Mesh mesh;
	std::vector<Model>	models = importer(path);
	mesh.indices = models[0].indices;
	mesh.bones = models[0].bones;
	for (auto i = 0; i < models[0].vertices.size(); ++i){
		Vert vert;
		vert.vertices = models[0].vertices[i];
		vert.normals = models[0].normals[i];
		vert.colors = models[0].colors[i];

		check_bones(vert, i + 1, models[0].bones);
		mesh.vertices.push_back(vert);
	}
	// for (auto i = 0; i < vertices.size(); ++i)
	// 	std::cout << "Vertice[" << i << "]: " "Bones affecting: "
	// 		<< vertices[i].bones[0] << ":" << vertices[i].weights[0] << " - "
	// 		<< vertices[i].bones[1] << ":" << vertices[i].weights[1] << " - " 
	// 		<< vertices[i].bones[2] << ":" << vertices[i].weights[2] << '\n' << std::endl;
	return mesh;
}