#pragma once

#include <glm/vec3.hpp>

#include <iostream>
#include <vector>

struct Model
{
	std::vector<glm::vec3>		vertices;
	std::vector<unsigned int>	indices;
};

std::vector<Model> importer(const char* path);