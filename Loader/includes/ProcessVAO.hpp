#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <assimp/mesh.h>

#include "Structs.hpp"
#include "Conversions.hpp"

struct VAOdata
{
	std::vector<Vert>			verts;
	std::vector<unsigned int>	indices;
};

VAOdata	process_vao(const aiMesh* mesh);