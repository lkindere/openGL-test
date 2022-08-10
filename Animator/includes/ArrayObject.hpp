#pragma once

#include <vector>

#include <glad/gl.h>

#include "Structs.hpp"

class ArrayObject {
	public:
		ArrayObject();
		void init(const std::vector<Vert>& vertices,
					const std::vector<GLuint>& indices, GLenum type);

	public:
		unsigned short nIndices() const;

	public:
		void bind() const;
		void unbind() const;

	private:
		GLuint			VAO;
		unsigned short	_nIndices;
};
