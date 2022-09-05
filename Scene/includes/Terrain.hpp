#pragma once

#define MAX_WIDTH 50
#define MAX_DEPTH 50

class Scene;

class Terrain
{
    public:
        Terrain(MeshData data, int ID, int shader, Scene* scene);

    public:

    private:
        char*                               _heightmap;
        int                                 _width;
        int                                 _height;
        Scene*                              _scene;
        int                                 _ID;
        int                                 _shaderID;
        ArrayObject                         _VAO;
};