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

void ArrayObject::updateInstances(const std::vector<glm::vec3>& positions, const std::vector<glm::mat4>& rotations){
    bind();
    unsigned int PositionBuffer;
    glGenBuffers(1, &PositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, PositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
    glVertexAttribDivisor(6, 1);

    unsigned int RotationBuffer;
    glGenBuffers(1, &RotationBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, RotationBuffer);
    glBufferData(GL_ARRAY_BUFFER, rotations.size() * sizeof(glm::mat4), rotations.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 16, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)0);
    glVertexAttribDivisor(7, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &PositionBuffer);
    glDeleteBuffers(1, &RotationBuffer);
    _instances = positions.size();
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
int            ArrayObject::instances() const { return _instances; }

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