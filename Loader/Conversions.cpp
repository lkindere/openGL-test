#include "Conversions.hpp"

glm::quat toGLquat(const aiQuaternion& aiQuat){
	return glm::quat(aiQuat.w, aiQuat.x, aiQuat.y, aiQuat.z);
}

glm::vec3 toGLvec(const aiVector3D& aiVec){
	return (glm::vec3(aiVec.x, aiVec.y, aiVec.z));
}

glm::vec4 toGLvec(const aiColor4D& aiCol){
	return (glm::vec4(aiCol.r, aiCol.g, aiCol.b, aiCol.a));
}

//Not sure if correct
glm::mat4	toGLmat(const aiMatrix4x4& aiMat){
    return 
    glm::mat4(
        glm::vec4(aiMat.a1, aiMat.b1, aiMat.c1, aiMat.d1),
        glm::vec4(aiMat.a2, aiMat.b2, aiMat.c2, aiMat.d2),
        glm::vec4(aiMat.a3, aiMat.b3, aiMat.c3, aiMat.d3),
        glm::vec4(aiMat.a4, aiMat.b4, aiMat.c4, aiMat.d4)
    );
    // glm::mat4(
    //     glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
    //     glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
    //     glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
    //     glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    // );
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
