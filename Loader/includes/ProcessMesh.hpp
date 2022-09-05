#pragma once

#include "main.hpp"

class aiScene;

MeshData process_mesh(const aiScene* scene);

struct image_data
{
    char* data;
    int x;
    int y;
    int channels;
};

image_data loadImage(const char* path);