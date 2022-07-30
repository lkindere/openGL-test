#pragma once

#include <glm/glm.hpp>

#include <glad/gl.h>
#include <vector>

//Vert color
struct Vert2v3
{
	glm::vec3 v1;
	glm::vec3 v2;
};

//Vert norm color
struct Vert3v3
{
	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;
};

template <class V>
class ArrayObject {
	public:
		ArrayObject() {}
		ArrayObject(std::vector<V>& vertices, std::vector<GLuint>& indices, GLenum type = GL_STATIC_DRAW){
			init(vertices, indices, type);
		}
		void init(std::vector<V>& vertices, std::vector<GLuint>& indices, GLenum type = GL_STATIC_DRAW){
			//Array
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			//Vertices
			GLuint VerticeBuffer;
			glGenBuffers(1, &VerticeBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, VerticeBuffer);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(V), vertices.data(), type);
			//Indices
			GLuint IndiceBuffer;
			glGenBuffers(1, &IndiceBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndiceBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), type);
			//Configure
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float)));
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
