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

void print_vec(const glm::quat& vec, bool sp){
	std::cout << "X: " << vec.x << " Y: "
        << vec.y << " Z: " << vec.z << " W: " << vec.w << '\n';
    if (sp)
        std::cout << std::endl;
}

void print_vec(const aiVector3D& vec, bool sp){
    print_vec(toGLvec(vec), sp);
}

void print_vec(const aiColor4D& vec, bool sp){
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

void print_bonedata(const std::vector<BoneData>& bonedata){
    // for (auto i = 0; i < bonedata.size(); ++i){
    //     std::cout << "Bone[" << i << "]: " << bonedata[i].name << '\n';
    //     if (bonedata[i].animations.size() != 0){
    //         for (auto j = 0; j < bonedata[i].animations.size(); ++j){
    //             std::cout << "  Animation [" << j << "]" << '\n';
    //             std::cout << "  Positions: " << bonedata[i].animations[j].positions.size() << '\n';
    //             std::cout << "  Rotations: " << bonedata[i].animations[j].rotations.size() << '\n';
    //             std::cout << "  Scales:    " << bonedata[i].animations[j].scales.size() << '\n';
    //             std::cout << std::endl;
    //         }
    //     }
    //     if (bonedata[i].children.size() != 0){
    //         std::cout << "  Children: ";
    //         for (auto j = 0; j < bonedata[i].children.size(); ++j)
    //             std::cout << '[' << bonedata[i].children[j] << "] ";
    //         std::cout << std::endl;
    //     }
    // }
    // std::cout << std::endl;
}

void print_keyframes(std::vector<KeyPosition>& positions){
    std::cout << "Positions:\n";
    for (auto i = 0; i < positions.size(); ++i){
        std::cout << "Timestamp: " << positions[i].timestamp << '\n';
        print_vec(positions[i].position);
    }
}

void print_keyframes(std::vector<KeyRotation>& rotations){
    std::cout << "Rotations:\n";
    for (auto i = 0; i < rotations.size(); ++i){
        std::cout << "Timestamp: " << rotations[i].timestamp << '\n';
        print_vec(rotations[i].rotation);
    }
}

void print_keyframes(std::vector<KeyScale>& scales){
    std::cout << "Scales:\n";
    for (auto i = 0; i < scales.size(); ++i){
        std::cout << "Timestamp: " << scales[i].timestamp << '\n';
        print_vec(scales[i].scale);
    }
}

void print_hierarchy(const NodeData& root, int spaces){
    char indent[spaces + 1];
    for (auto i = 0; i < spaces; ++i)
        indent[i] = ' ';
    indent[spaces] = '\0';
    std::cout << indent << "Node:     " << root.name << '\n';
    std::cout << indent << "Children: " << root.children.size() << '\n';
    glm::mat4 mat(root.transformation);
    for (auto i = 0; i < 4; ++i){
        std::cout << indent << "X: " << mat[i].x << " Y: " << mat[i].y
            << " Z: " << mat[i].z << " W: " << mat[i].w << '\n';
    }
    std::cout << '\n' << std::endl;
    for (auto i = 0; i < root.children.size(); ++i){
        print_hierarchy(root.children[i], spaces + 4);
    }
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
    std::cout << indent << "N meshes: " << root->mNumMeshes << '\n';
    std::cout << indent;
    for (auto i = 0; i < root->mNumMeshes; ++i)
        std::cout << root->mMeshes[i] << ' ';
    std::cout << '\n' << std::endl;
    for (auto i = 0; i < root->mNumChildren; ++i){
        print_hierarchy(root->mChildren[i], spaces + 4);
    }
}
