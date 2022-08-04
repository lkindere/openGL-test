#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

#include <assimp/vector3.h>
#include <assimp/matrix4x4.h>

glm::quat toGLquat(const aiQuaternion& aiQuat){
	return glm::quat(aiQuat.x, aiQuat.y, aiQuat.z, aiQuat.w);
}

glm::vec3 toGLvec(const aiVector3D& aiVec){
	return (glm::vec3(aiVec.x, aiVec.y, aiVec.z));
}

glm::vec4 toGLvec(const aiColor4D& aiCol){
	return (glm::vec4(aiCol.r, aiCol.g, aiCol.b, aiCol.a));
}

//Not sure if correct
glm::mat4	toGLmat(const aiMatrix4x4& aiMat){
	glm::vec4 v1(aiMat.a1, aiMat.a2, aiMat.a3, aiMat.a4);
	glm::vec4 v2(aiMat.b1, aiMat.b2, aiMat.b3, aiMat.b4);
	glm::vec4 v3(aiMat.c1, aiMat.c2, aiMat.c3, aiMat.c4);
	glm::vec4 v4(aiMat.d1, aiMat.d2, aiMat.d3, aiMat.d4);
	return (glm::mat4(v1, v2, v3, v4));
}

static bool same_float(float a, float b){
	return (fabs(a - b) < 0.01);
}

bool same_vec(const glm::vec3& v1, const glm::vec3& v2){
	return (same_float(v1.x, v2.x)
			&& same_float(v1.y, v2.y)
			&& same_float(v1.z, v2.z));
}

bool same_quat(const glm::quat& q1, const glm::quat& q2){
	return (same_float(q1.x, q2.x)
			&& same_float(q1.y, q2.y)
			&& same_float(q1.z, q2.z)
			&& same_float(q1.w, q2.w));
}
