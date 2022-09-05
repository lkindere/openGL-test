#pragma once

#include "main.hpp"

#include <assimp/vector3.h>
#include <assimp/color4.h>
#include <assimp/matrix4x4.h>
#include <assimp/quaternion.h>

glm::quat toGLquat(const aiQuaternion& aiQuat);
glm::vec3 toGLvec(const aiVector3D& aiVec);
glm::vec4 toGLvec(const aiColor4D& aiCol);
glm::mat4 toGLmat(const aiMatrix4x4& aiMat);

static bool same_float(float a, float b);
bool same_vec(const glm::vec3& v1, const glm::vec3& v2);
bool same_quat(const glm::quat& q1, const glm::quat& q2);