#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
};

class VBO {
   public:
    VBO(std::vector<Vertex>& vertices);
    void bind();
    void unbind();
    void destroy();

   private:
    GLuint ID;
};
