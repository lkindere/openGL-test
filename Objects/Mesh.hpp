#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <vector>

#include "Shader.hpp"
#include "Camera.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

class Mesh
{
	public:
		Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
		void Draw(Shader& shader, Camera& camera);
	private:
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		VAO VAO;
};