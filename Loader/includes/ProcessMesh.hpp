#pragma once

#include <vector>
#include <stdexcept>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <assimp/scene.h>
#include <assimp/mesh.h>

#include "Structs.hpp"
#include "Conversions.hpp"

MeshData process_mesh(const aiNode* root, const aiMesh* mesh);