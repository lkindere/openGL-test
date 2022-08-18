#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>

#include <iostream>

//All names matching locateBones will calculate average position
struct LoadingParameters
{
    std::vector<std::string>    locateBones;
};

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

//Only used for importing

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
    std::vector<AnimData>       animations;
    std::unique_ptr<glm::vec3>  position = nullptr;
    std::unique_ptr<glm::mat4>  postTransform = nullptr;
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
            assert(bone != nullptr && bone->position != nullptr);
            return *(bone->position);
        }
        void postTransform(const glm::mat4& transform) const {
            assert(bone != nullptr);
            bone->postTransform = std::unique_ptr<glm::mat4>(new glm::mat4(transform));
        }
};

struct AnimTimers
{
    float duration;
    float tps;
};

struct HitboxData
{
    std::vector<glm::vec3>      vertices;
    std::vector<unsigned int>   indices;
};

struct MeshData
{
    std::vector<Vert>                   verts;
    std::vector<unsigned int>           indices;
    NodeData                            nodes;
    std::vector<AnimTimers>             timers;
    TextureData                         texture;
    HitboxData                          hitbox;
};

