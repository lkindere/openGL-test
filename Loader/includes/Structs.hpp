#pragma once

#include <vector>
#include <string>

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

struct AnimData
{
    std::vector<KeyPosition>    positions;
    std::vector<KeyRotation>    rotations;
    std::vector<KeyScale>       scales;
};

struct BoneData
{
    std::string                 name;
    glm::mat4                   transform;
    glm::mat4                   offset;
    std::vector<AnimData>       animations;
    std::vector<unsigned short> children;
};

struct AnimTimers
{
    float duration;
    float tps;
};

struct MeshData
{
    std::vector<Vert>			verts;
    std::vector<unsigned int>	indices;
    std::vector<BoneData>       bones;
    std::vector<AnimTimers>     timers;
    glm::mat4                   transformation;
    glm::mat4                   inverse;
};

