#include "ArrayObject.hpp"

ArrayObject::ArrayObject(const MeshData& data, GLenum type){
    init(data, type);
}

ArrayObject::~ArrayObject() {
    destroy();
}

void ArrayObject::init(const MeshData& data, GLenum type){
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

void ArrayObject::updateInstances(const std::vector<InstanceData>& instances){
	// glBindVertexArray(_VAO);
    glDeleteBuffers(1, &_instanceBuffer);
    glGenBuffers(1, &_instanceBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, _instanceBuffer);
    // std::cout << "Instance Buffer: " << _instanceBuffer << std::endl;
    // glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(InstanceData), instances.data(), GL_STATIC_DRAW);
    // //Pos
    // glEnableVertexAttribArray(6);
	// std::cout << glGetError() << std::endl;
    // glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void *)0);
    // glVertexAttribDivisor(6, 1);
    // //Rot line1
    // glEnableVertexAttribArray(7);
    // glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void *)(3 * sizeof(float)));
    // glVertexAttribDivisor(7, 1);
    // //Rot line2
    // glEnableVertexAttribArray(8);
    // glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void *)(6 * sizeof(float)));
    // glVertexAttribDivisor(8, 1);
    // //Rot line3
    // glEnableVertexAttribArray(9);
    // glVertexAttribPointer(9, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void *)(9 * sizeof(float)));
    // glVertexAttribDivisor(9, 1);

    // glDeleteBuffers(1, &_instanceBuffer);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ArrayObject::initTexture(const TextureData& texture){
    if (texture.data == nullptr)
        return ;
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

void ArrayObject::destroy() {
    glDeleteVertexArrays(1, &_VAO);
}