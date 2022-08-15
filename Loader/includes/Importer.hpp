#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ProcessMesh.hpp"

MeshData importer(const char* path, const std::vector<std::string>& limbs = std::vector<std::string>());