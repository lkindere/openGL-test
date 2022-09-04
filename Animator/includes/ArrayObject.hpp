#pragma once

#include "main.hpp"
#include <glad/gl.h>

#define MAX_BONES 30
#define MAX_INSTANCES 1000

struct InstanceData
{
    glm::vec3 position;
    glm::vec3 rotL1;
    glm::vec3 rotL2;
    glm::vec3 rotL3;
    float     time = 0;
    int       flags = 0;
};

struct InstanceBoneData
{
    std::vector<glm::mat4> matrices;
    InstanceBoneData(std::vector<glm::mat4> mats)
        : matrices(std::move(mats)) {}
};

class ArrayObject {
	public:
		ArrayObject(const MeshData& data);
        ~ArrayObject();
    private:
		void init(const MeshData& data);
        void initTexture(const TextureData& texture);
        void generateBoneBuffer();

	public:
        bool            hasTexture() const;
		unsigned short  nIndices() const;
    

	public:
        void updateInstances(const std::vector<InstanceData>& instances,
            const std::vector<InstanceBoneData>& bones = std::vector<InstanceBoneData>());
        void deleteInstanceBuffer();
		void bind() const;
		void unbind() const;
        void destroy();

	private:
        GLuint          _shaderID = -1;
		GLuint			_VAO = -1;
        GLuint          _texture = -1;
		unsigned short	_nIndices = 0;
        GLuint          _instanceBuffer = -1;
        GLuint          _boneBuffer = -1;
        GLuint          _boneTexture = -1;
};
