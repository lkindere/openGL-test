#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>
#include <map>
#include <utility>

#define MAX_WEIGHTS	3
#define MAX_BONES 

struct KeyPosition
{
	glm::vec3	position;
	float		timestamp;
};

struct KeyRotation
{
	glm::quat	rotation;
	float		timestamp;
};

struct KeyScale
{
	glm::vec3	scale;
	float		timestamp;
};

//ID of the bone
//Weight map with indexes and floats
//Matrix offset from mesh space to bone space
struct Bone
{
	unsigned short					ID;
	//Not needed after loading the info to vertices
	std::map<unsigned int, float>	weights;
	glm::mat4						offset;
	std::vector<KeyPosition>		positions;
	std::vector<KeyRotation>		rotations;
	std::vector<KeyScale>			scales;
	std::string						name;
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