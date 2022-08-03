#pragma once

#include <vector>

#include <glad/gl.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "Importer.hpp"

    // Shader shader("Shaders/default.vert", "Shaders/default.frag");
	// Shader lightShader("Shaders/light.vert", "Shaders/light.frag");

	// std::cout << "Loading sword\n";
	// std::vector<Model> meshes = importer("Models/sword.fbx");
	// std::vector<Vert> vertices = convert_vertices(meshes);
	// Player player(vertices, meshes[0].indices);
	
	// player.setWeapon(new Sword(vertices, meshes[0].indices));

	// std::cout << "Loading light\n";
	// meshes = importer("Models/light.fbx");
	// vertices = convert_vertices(meshes);
	// Light light(vertices, meshes[0].indices);
	// light.addTarget(shader);

	// std::cout << "Loading bones\n";
	// meshes = importer("Models/bones.fbx");
	// vertices = convert_vertices(meshes);
	// Mob mob(vertices, meshes[0].indices);

	// std::cout << "Loading floor\n";
	// meshes = importer("Models/floor.fbx");
	// vertices = convert_vertices(meshes);
	// Object floor(vertices, meshes[0].indices);
	// player.camera.addShader(shader);
	// player.camera.addShader(lightShader);

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
	std::vector<Vert> vertices;
	std::vector<GLuint> indices;
};

// std::vector<Vert> convert_vertices(std::vector<Model>& meshes){
// 	std::vector<Vert>	vertices;
// 	for (auto i = 0; i < meshes[0].vertices.size(); ++i){
// 		Vert vert;
// 		vert.vertices = meshes[0].vertices[i];
// 		vert.normals = meshes[0].normals[i];
// 		vert.colors = meshes[0].colors[i];
// 		vertices.push_back(vert);
// 	}
// 	return vertices;
// }


//Indexes start from 1
void check_bones(Vert& vert, unsigned int index, const std::vector<Bone>& bones){
	for (auto i = 0; i < bones.size(); ++i){
		for (auto j = 0; j < 3; ++j){
			if (bones[i].vertices[j] == index)
				std::cout << index << ":Vertex match: " << bones[i].vertices[j] << " I:" << i << " J: " << j << " weight: " << bones[i].weights[j] << std::endl;
		}
	}
	// unsigned int	matches[MAX_WEIGHTS] = {0};
	// float			weights[MAX_WEIGHTS] = {0.0f};
	// unsigned int	counter = 0;
	// for (auto i = 0; i < bones.size(); ++i){
	// 	for (auto j = 0; j < MAX_WEIGHTS; ++j){
	// 		if (bones[i].vertices[j] == index){
	// 			// std::cout << "Matched bone[" << i << "] vert: " << bones[i].vertices[j] << std::endl;
	// 			matches[counter] = bones[i].vertices[j];
	// 			weights[counter] = bones[i].weights[j];
	// 			++counter;
	// 		}
	// 	}
	// }
// #ifdef DEBUG
// 	if (counter > MAX_WEIGHTS)
// 		std::cout << "Too many bone matches per vertex while loading\n" << std::endl;
// #endif
}

Mesh load_mesh(const char* path){
#ifdef DEBUG
	std::cout << "Loading: " << path << std::endl;
#endif
	std::vector<Model>	models = importer(path);
	std::vector<Vert>	vertices;
	std::vector<GLuint>	indices(models[0].indices);
	for (auto i = 0; i < models[0].vertices.size(); ++i){
		Vert vert;
		vert.vertices = models[0].vertices[i];
		vert.normals = models[0].normals[i];
		vert.colors = models[0].colors[i];

		check_bones(vert, i + 1, models[0].bones);
		vertices.push_back(vert);
	}
	exit(0);
}