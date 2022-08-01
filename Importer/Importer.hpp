#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <iostream>
#include <vector>

struct Model
{
	std::vector<glm::vec3>		vertices;
	std::vector<glm::vec3>		normals;
	std::vector<glm::vec4>		colors;
	std::vector<unsigned int>	indices;
};

std::vector<Model> importer(const char* path);