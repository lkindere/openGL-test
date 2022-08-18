#include "Hitbox.hpp"
#include "settings.hpp"

extern Settings settings;
extern Shader* g_hitboxShader;

Hitbox::Hitbox() {}

bool Hitbox::checkCollision(const Hitbox& hitbox) const {
    return true;
}

void Hitbox::updateHitbox(const glm::mat4& transformation){
    _transformation = transformation;
}

void Hitbox::init(HitboxData& data){
    _vertices = std::move(data.vertices);
    std::cout << "Hitbox:\n";
    for (auto i = 0; i < _vertices.size(); ++i)
        settings.printvec(_vertices[i]);

    //Nede to always update a copy and keep inits as backup probs;
}

void Hitbox::draw(const Shader& shader, Uniforms uniforms) const{
    std::vector<glm::vec3>  transformedVertices;
    transformedVertices.reserve(_vertices.size());
    for (auto i = 0; i < _vertices.size(); ++i)
        transformedVertices.push_back(_transformation * glm::vec4(_vertices[i], 1.0f));

    g_hitboxShader->bind();
    g_hitboxShader->update(uniforms);

    GLuint temp;
    glGenVertexArrays(1, &temp);
	glBindVertexArray(temp);

    GLuint VerticeBuffer;
	glGenBuffers(1, &VerticeBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VerticeBuffer);
	glBufferData(GL_ARRAY_BUFFER, transformedVertices.size() * sizeof(glm::vec3), transformedVertices.data(), GL_STREAM_DRAW);

    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_LINES, 0, _vertices.size());
    glBindVertexArray(0);

    glDeleteBuffers(1, &VerticeBuffer);
    glDeleteVertexArrays(1, &temp);
    g_hitboxShader->unbind();
}


// void Hitbox::initVAO(){
//     //Array
// 	glGenVertexArrays(1, &_VAO);
// 	glBindVertexArray(_VAO);

// 	//Vertices
// 	GLuint VerticeBuffer;
// 	glGenBuffers(1, &VerticeBuffer);
// 	glBindBuffer(GL_ARRAY_BUFFER, VerticeBuffer);
// 	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), _vertices.data(), GL_STATIC_DRAW);

// 	//Vertice
// 	glEnableVertexAttribArray(0);
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

// 	//Unbind
// 	glBindVertexArray(0);
// 	glBindBuffer(GL_ARRAY_BUFFER, 0);

// 	//Delete
// 	glDeleteBuffers(1, &VerticeBuffer);
// }

