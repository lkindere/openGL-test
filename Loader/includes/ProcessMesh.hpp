#pragma once

#include "main.hpp"
#include "Conversions.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>

MeshData process_mesh(const aiScene* scene);