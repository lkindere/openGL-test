#include "debug.hpp"

void print_vec(const glm::vec3& vec, bool sp){
	std::cout << "X: " << vec.x << " Y: "
        << vec.y << " Z: " << vec.z << '\n';
    if (sp)
        std::cout << std::endl;
}

void print_vec(const glm::vec4& vec, bool sp){
	std::cout << "X: " << vec.x << " Y: "
        << vec.y << " Z: " << vec.z << " W: " << vec.w << '\n';
    if (sp)
        std::cout << std::endl;
}

void print_vec(const aiVector3D& vec, bool sp = true){
    print_vec(toGLvec(vec), sp);
}

void print_vec(const aiColor4D& vec, bool sp = true){
    print_vec(toGLvec(vec), sp);
}

void print_mat(const glm::mat3& mat){
    print_vec(mat[0], 0);
    print_vec(mat[1], 0);
    print_vec(mat[2], 0);
    std::cout << std::endl;
}

void print_mat(const glm::mat4& mat){
    print_vec(mat[0], 0);
    print_vec(mat[1], 0);
    print_vec(mat[2], 0);
    print_vec(mat[3], 0);
    std::cout << std::endl;
}

void print_mat(const aiMatrix4x4& mat){
    print_mat(toGLmat(mat));
}

void print_hierarchy(const aiNode* root, int spaces){
    char indent[spaces + 1];
    for (auto i = 0; i < spaces; ++i)
        indent[i] = ' ';
    indent[spaces] = '\0';
    std::cout << indent << "Node:     " << root->mName.data << '\n';
    std::cout << indent << "Children: " << root->mNumChildren << '\n';
    glm::mat4 mat(toGLmat(root->mTransformation));
    for (auto i = 0; i < 4; ++i){
        std::cout << indent << "X: " << mat[i].x << " Y: " << mat[i].y
            << " Z: " << mat[i].z << " W: " << mat[i].w << '\n';
    }
    std::cout << std::endl;
    for (auto i = 0; i < root->mNumChildren; ++i){
        print_hierarchy(root->mChildren[i], spaces + 4);
    }
}
