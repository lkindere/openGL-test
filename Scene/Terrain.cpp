#include "Scene.hpp"
#include "Terrain.hpp"
#include "ProcessMesh.hpp"

Terrain::Terrain(MeshData data, int ID, int shader, Scene* scene)
    : _VAO(data), _ID(ID), _shaderID(shader), _scene(scene){
    image_data idata = loadImage("_Blender/heightmap.jpg");
    _width = idata.x;
    _height = idata.y;
    _heightmap = idata.data;
    std::cout << "Width: " << _width << " height: " << _height << std::endl;
    std::cout << "Data ptr: " << idata.data << std::endl;
    for (auto i = 0; i < _width; ++i)
            std::cout << (int)_heightmap[i] << ' ';
    exit(0);
}