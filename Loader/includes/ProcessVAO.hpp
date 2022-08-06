#pragma once

#include <vector>
#include <stdexcept>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <assimp/mesh.h>

#include "Structs.hpp"
#include "Conversions.hpp"

VAOdata	process_vao(const aiMesh* mesh);