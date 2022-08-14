#include "ArrayObject.hpp"

#include <iostream>

ArrayObject::ArrayObject() : _nIndices(0) {}

void ArrayObject::init(const MeshData& data, GLenum type = GL_STATIC_DRAW){
    const std::vector<Vert>&            vertices = data.verts;
    const std::vector<unsigned int>&    indices = data.indices;
    //Array
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
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
	_nIndices = indices.size();
	//Vertice
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void *)0);
	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void *)(3 * sizeof(float)));
	//Color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vert), (void *)(6 * sizeof(float)));
    //Tex coords
    glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (void *)(10 * sizeof(float)));
	//Bones
	glEnableVertexAttribArray(4);
	glVertexAttribIPointer(4, 3, GL_INT, sizeof(Vert), (void *)(12 * sizeof(float)));
	//Weights
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void *)(12 * sizeof(float) + 3 * sizeof(int)));
	//Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//Delete
	glDeleteBuffers(1, &VerticeBuffer);
	glDeleteBuffers(1, &IndiceBuffer);
    initTexture(data.texture);
}

void ArrayObject::initTexture(const TextureData& texture){
    if (texture.data == nullptr){
        std::cout << "NO TEXTURE\n";
        return ;
    }
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);
    glGenerateMipmap(GL_TEXTURE_2D);

}

bool           ArrayObject::hasTexture() const { return _texture != -1; }
unsigned short ArrayObject::nIndices() const { return _nIndices; }

void ArrayObject::bind() const {
    glBindVertexArray(_VAO);
    if (_texture != -1)
        glBindTexture(GL_TEXTURE_2D, _texture);
}
void ArrayObject::unbind() const {
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
