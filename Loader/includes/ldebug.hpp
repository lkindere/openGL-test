#pragma once

#include "main.hpp"
#include "Conversions.hpp"

#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/anim.h>


void print_vec(const glm::ivec3& vec, bool sp = true);
void print_vec(const glm::vec3& vec, bool sp = true);
void print_vec(const glm::vec4& vec, bool sp = true);
void print_vec(const aiVector3D& vec, bool sp = true);
void print_vec(const aiColor4D& vec, bool sp = true);
void print_vec(const aiTexel& vec, bool sp = true);
void print_vec(const glm::quat& vec, bool sp = true);

void print_mat(const glm::mat3& mat);
void print_mat(const glm::mat4& mat);
void print_mat(const aiMatrix4x4& mat);

void print_keyframes(std::vector<KeyPosition>& positions);
void print_keyframes(std::vector<KeyRotation>& rotations);
void print_keyframes(std::vector<KeyScale>& scales);

void print_vertices(const std::vector<Vert>& verts);
void print_hierarchy(const NodeData& root, int spaces = 0);
void print_hierarchy(const aiNode* root, int spaces = 0);