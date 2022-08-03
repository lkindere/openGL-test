#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <vector>

#define MAX_WEIGHTS	3
#define MAX_BONES 

//ID of the specific bone
//Array of vertices affected
//Array of weights for affected vertices
//Matrix offset from mesh space to bone space
struct Bone
{
	unsigned short	ID;
	unsigned int	vertices[MAX_WEIGHTS];
	float			weights[MAX_WEIGHTS];
	glm::mat4		offset;
};

struct Model
{
	std::vector<glm::vec3>		vertices;
	std::vector<glm::vec3>		normals;
	std::vector<glm::vec4>		colors;
	std::vector<unsigned int>	indices;
	std::vector<Bone>			bones;
};

std::vector<Model> importer(const char* path);