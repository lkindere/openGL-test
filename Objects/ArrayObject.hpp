#pragma once

#include <glm/glm.hpp>

#include <glad/gl.h>
#include <vector>

struct Vert
{
	glm::vec3	vertices;
	glm::vec3	normals;
	glm::vec4	colors;
};

class ArrayObject {
	public:
		ArrayObject() {}
		ArrayObject(std::vector<Vert>& vertices, std::vector<GLuint>& indices, GLenum type = GL_STATIC_DRAW){
			init(vertices, indices, type);
		}
		void init(std::vector<Vert>& vertices, std::vector<GLuint>& indices, GLenum type = GL_STATIC_DRAW){
			//Array
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			//Vertices
			GLuint VerticeBuffer;
			glGenBuffers(1, &VerticeBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, VerticeBuffer);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vert), vertices.data(), type);
			//Indices
			GLuint IndiceBuffer;
			glGenBuffers(1, &IndiceBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndiceBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), type);
			//Configure
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void *)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void *)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void *)(6 * sizeof(float)));
			//Unbind
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			//Delete
			glDeleteBuffers(1, &VerticeBuffer);
			glDeleteBuffers(1, &IndiceBuffer);
		}
		void bind() { glBindVertexArray(VAO); }
		void unbind() { glBindVertexArray(0); }
	
	private:
		GLuint VAO;
};
