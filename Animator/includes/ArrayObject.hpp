#pragma once

#include <vector>

#include <glad/gl.h>

#include "Structs.hpp"

class ArrayObject {
	public:
		ArrayObject();
        ~ArrayObject();
		void init(const MeshData& data, GLenum type);

	public:
        bool            hasTexture() const;
		unsigned short  nIndices() const;
    
    private:
        void initTexture(const TextureData& texture);

	public:
		void bind() const;
		void unbind() const;
        void destroy();

	private:
		GLuint			_VAO = -1;
        GLuint          _texture = -1;
		unsigned short	_nIndices = 0;
};
