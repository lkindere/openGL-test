#pragma once

#include <vector>

#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/anim.h>

#include "Bone.hpp"
#include "Structs.hpp"
#include "Conversions.hpp"

std::vector<Bone> process_bones(const aiMesh* mesh, const aiAnimation* animation, const aiNode* root);
