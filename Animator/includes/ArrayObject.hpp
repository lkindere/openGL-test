#pragma once

#include "main.hpp"
#include <glad/gl.h>

struct InstanceData
{
    glm::vec3 position;
    glm::vec3 rotL1;
    glm::vec3 rotL2;
    glm::vec3 rotL3;
};

class ArrayObject {
	public:
		ArrayObject(const MeshData& data, GLenum type = GL_STATIC_DRAW);
        ~ArrayObject();
    private:
		void init(const MeshData& data, GLenum type);

	public:
        bool            hasTexture() const;
		unsigned short  nIndices() const;
    
    private:
        void initTexture(const TextureData& texture);

	public:
        void updateInstances(const std::vector<InstanceData>& instances);
		void bind() const;
		void unbind() const;
        void destroy();

	private:
		GLuint			_VAO = -1;
        GLuint          _instanceBuffer = -1;
        GLuint          _texture = -1;
		unsigned short	_nIndices = 0;
};
