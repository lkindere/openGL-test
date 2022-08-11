#pragma once

#include <vector>
#include <iostream>

#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/anim.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Structs.hpp"
#include "Conversions.hpp"

void print_vec(const glm::vec3& vec, bool sp = true);
void print_vec(const glm::vec4& vec, bool sp = true);
void print_vec(const aiVector3D& vec, bool sp = true);
void print_vec(const aiColor4D& vec, bool sp = true);
void print_vec(const glm::quat& vec, bool sp = true);

void print_mat(const glm::mat3& mat);
void print_mat(const glm::mat4& mat);
void print_mat(const aiMatrix4x4& mat);

void print_keyframes(std::vector<KeyPosition>& positions);
void print_keyframes(std::vector<KeyRotation>& rotations);
void print_keyframes(std::vector<KeyScale>& scales);

// void print_bonedata(const std::vector<BoneData>& bonedata);
void print_hierarchy(const NodeData& root, int spaces = 0);
void print_hierarchy(const aiNode* root, int spaces = 0);