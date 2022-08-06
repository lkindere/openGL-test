#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>

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

struct Vert
{
	glm::vec3	vertices;
	glm::vec3	normals;
	glm::vec4	colors;
	glm::ivec3	bones;
	glm::vec3	weights;
};

//Only used for importing
struct VAOdata
{
	std::vector<Vert>			verts;
	std::vector<unsigned int>	indices;
};