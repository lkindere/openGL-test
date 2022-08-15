#pragma once

#include <map>
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
    glm::vec2   textures;
	glm::ivec3	bones;
	glm::vec3	weights;
};

struct TextureData
{
    int             width;
    int             height;
    int             channels;
    unsigned char*  data;
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
    unsigned short              ID;
    glm::mat4                   offset;
    std::vector<AnimData>       animations;
};

struct NodeData
{
    std::string             name;
    BoneData*               bone;
    std::vector<NodeData>   children;
    glm::mat4               transformation;
};

struct AnimTimers
{
    float duration;
    float tps;
};

struct LimbData
{
    std::string     name;
    unsigned short  boneID;
    glm::vec3       position;
};

struct MeshData
{
    std::vector<Vert>                   verts;
    std::vector<unsigned int>           indices;
    NodeData                            nodes;
    std::vector<AnimTimers>             timers;
    TextureData                         texture;
    std::vector<LimbData>               limbs;
};

