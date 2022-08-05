#pragma once

#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/anim.h>

#include <vector>

#include "Bone.hpp"
#include "Structs.hpp"
#include "Conversions.hpp"

std::vector<Bone> process_bones(const aiMesh* mesh, const aiAnimation* animation, const aiNode* root);
