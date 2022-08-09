#pragma once

#include <vector>

#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/anim.h>

#include "Structs.hpp"
#include "Conversions.hpp"

std::vector<AnimTimers> process_animations(const aiNode* root, const aiScene* scene, std::vector<BoneData>& bones);