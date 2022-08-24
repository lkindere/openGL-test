#pragma once

#include <map>
#include <vector>
#include <stdexcept>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>

#include "Structs.hpp"
#include "Conversions.hpp"

MeshData process_mesh(const aiScene* scene);