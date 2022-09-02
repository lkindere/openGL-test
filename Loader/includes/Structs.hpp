#pragma once

#include "main.hpp"

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
    unsigned char*  data = nullptr;
};

struct AnimData
{
    std::vector<KeyPosition>    positions;
    std::vector<KeyRotation>    rotations;
    std::vector<KeyScale>       scales;
};

struct BoneData
{
    short                       ID;
    glm::mat4                   offset;
    glm::vec3                   position;
    std::vector<AnimData>       animations;
};

struct NodeData
{
    std::string                 name;
    std::vector<NodeData>       children;
    glm::mat4                   transformation;
    std::unique_ptr<BoneData>   bone = nullptr;

    public:
        short ID() const {
            assert(bone != nullptr);
            return bone->ID;
        }
        glm::vec3 position() const {
            assert(bone != nullptr);
            return bone->position;
        }
};

struct AnimTimers
{
    float duration;
    float tps;
};

struct HitboxData
{
    std::vector<glm::vec3> vertices;
    glm::vec3 min;
    glm::vec3 max;
};

struct MeshData
{
    std::vector<Vert>                   verts;
    std::vector<unsigned int>           indices;
    std::vector<AnimTimers>             timers;
    NodeData                            nodes;
    TextureData                         texture;
    HitboxData                          hitbox;
    int                                 nBones;
};

