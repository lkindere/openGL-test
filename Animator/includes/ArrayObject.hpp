#pragma once

#include "main.hpp"
#include <glad/gl.h>

class ArrayObject {
	public:
		ArrayObject(const MeshData& data, GLenum type = GL_STATIC_DRAW);
        ~ArrayObject();
    private:
		void init(const MeshData& data, GLenum type);

	public:
        bool            hasTexture() const;
		unsigned short  nIndices() const;
        int             instances() const;
    
    private:
        void initTexture(const TextureData& texture);

	public:
        void updateInstances(const std::vector<glm::vec3>& positions, const std::vector<glm::mat4>& rotations);
		void bind() const;
		void unbind() const;
        void destroy();

	private:
		GLuint			_VAO = -1;
        GLuint          _texture = -1;
        int             _instances = -1;
		unsigned short	_nIndices = 0;
};
