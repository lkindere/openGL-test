#include "ArrayObject.hpp"

ArrayObject::ArrayObject(const MeshData& data){
    init(data);
}

ArrayObject::~ArrayObject() {
    destroy();
}

void ArrayObject::init(const MeshData& data){
    const std::vector<Vert>&            vertices = data.verts;
    const std::vector<unsigned int>&    indices = data.indices;
    //Array
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	//Vertices
	GLuint VerticeBuffer;
	glGenBuffers(1, &VerticeBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VerticeBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vert), vertices.data(), GL_STATIC_DRAW);
	//Indices
	GLuint IndiceBuffer;
	glGenBuffers(1, &IndiceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndiceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
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
    if (texture.data == nullptr)
        return ;
    glGenTextures(1, &_texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void ArrayObject::generateBoneBuffer(){
    glGenBuffers(1, &_boneBuffer);
    glBindBuffer(GL_TEXTURE_BUFFER, _boneBuffer);
    glBufferData(GL_TEXTURE_BUFFER, MAX_BONES * MAX_INSTANCES * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);

    glGenTextures(1, &_boneTexture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_BUFFER, _boneTexture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, _boneBuffer);

    glBindBuffer(GL_TEXTURE_BUFFER, 0);
}

void ArrayObject::updateInstances(const std::vector<InstanceData>& instances,
                                    const std::vector<InstanceBoneData>& bones){
    glGenBuffers(1, &_instanceBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _instanceBuffer);
    glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(InstanceData), instances.data(), GL_STATIC_DRAW);
    //Pos
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void *)0);
    glVertexAttribDivisor(6, 1);
    // Rot line1
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void *)(3 * sizeof(float)));
    glVertexAttribDivisor(7, 1);
    //Rot line2
    glEnableVertexAttribArray(8);
    glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void *)(6 * sizeof(float)));
    glVertexAttribDivisor(8, 1);
    //Rot line3
    glEnableVertexAttribArray(9);
    glVertexAttribPointer(9, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void *)(9 * sizeof(float)));
    glVertexAttribDivisor(9, 1);
    //Time
    glEnableVertexAttribArray(10);
    glVertexAttribPointer(10, 1, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void *)(12 * sizeof(float)));
    glVertexAttribDivisor(10, 1);
    //Flags
    glEnableVertexAttribArray(11);
    glVertexAttribPointer(11, 1, GL_INT, GL_FALSE, sizeof(InstanceData), (void *)(13 * sizeof(float)));
    glVertexAttribDivisor(11, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (bones.size() != 0){
        if (_boneBuffer == -1)
            generateBoneBuffer();
        std::cout << "Bones size: " << bones.size() << std::endl;
        for (auto i = 0; i < bones.size(); ++i){
            std::cout << "Bone " << i << " size: " << bones[i].matrices.size() << std::endl;
        }
        std::cout << "Bone buffer: " << _boneBuffer << std::endl;
        glBindBuffer(GL_TEXTURE_BUFFER, _boneBuffer);
        for (auto i = 0; i < bones.size(); ++i){
            glBufferSubData(GL_TEXTURE_BUFFER, i * sizeof(glm::mat4) * MAX_BONES, bones[i].matrices.size() * sizeof(glm::mat4), bones[i].matrices.data());

        }

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_BUFFER, _boneTexture);

        glBindBuffer(GL_TEXTURE_BUFFER, 0);
    }
}

void ArrayObject::deleteInstanceBuffer(){
    glBindVertexArray(0);
    glDeleteBuffers(1, &_instanceBuffer);
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