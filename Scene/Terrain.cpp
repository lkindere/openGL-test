#include "Scene.hpp"
#include "Uniforms.hpp"
#include "Terrain.hpp"
#include "ProcessMesh.hpp"

Terrain::Terrain(MeshData data, int ID, int shader, Scene* scene)
    : _VAO(std::move(data)), _ID(ID), _shaderID(shader), _scene(scene){
        std::cout << "Loaded terrain VAO\n";
    image_data idata = loadImage("_Blender/5050.png");
    _width = idata.x;
    _height = idata.y;
    _heightmap = idata.data;
    // std::cout << "Width: " << _width << " height: " << _height << std::endl;
    // std::cout << "Data ptr: " << idata.data << std::endl;
    unsigned short min = 256;
    unsigned short max = 0;
    for (auto j = 0; j < _height; ++j){
        for (auto i = 0; i < _width; ++i){
            if ((int)((unsigned char)(_heightmap[i + j * _width])) > max)
                max = (int)((unsigned char)(_heightmap[i + j * _width]));
            if ((int)((unsigned char)(_heightmap[i + j * _width])) < min)
                min = (int)((unsigned char)(_heightmap[i + j * _width]));
            // std::cout << (int)((unsigned char)(_heightmap[i + j * _width])) << ' ';
        }
        // std::cout << '\n';
    }
    float vmin = data.verts[0].vertices.y;
    float vmax = data.verts[0].vertices.y;
    for (auto i = 0; i < data.verts.size(); ++i){
        printvec(data.verts[i].vertices);
        if (data.verts[i].vertices.y < vmin)
            vmin = data.verts[i].vertices.y;
        else if (data.verts[i].vertices.y > vmax)
            vmax = data.verts[i].vertices.y;
    }
    // std::cout << "Max value: " << max << std::endl;
    // std::cout << "Min value: " << min << std::endl;
    // std::cout << "vMax value: " << vmax << std::endl;
    // std::cout << "vMin value: " << vmin << std::endl;
    // std::cout << "Verts size: " << data.verts.size() << std::endl;
    // exit(0);

    //Map 0.0f to 0 heightmap
    //Map vertices max y to heightmap max y
    //Everything else if interpolated between the 2
}

float Terrain::height(const glm::vec3& pos) const {
    // assert(pos.x <= width && pos.z <= height);
}

void Terrain::draw(Uniforms uniforms){
    _VAO.bind();
    const Shader* shader = _scene->shader(_shaderID);
    std::cout << "Shader ID: " << _shaderID << std::endl;
    shader->bind();
    shader->update(uniforms);
    glUniform1i(glGetUniformLocation(shader->ID(), "modelFlags"), 0);

    std::vector<InstanceData> instance;
    InstanceData data;
    data.position = glm::vec3(0.0f);
    data.rotL1 = glm::vec3(1.0f, 0.0f, 0.0f);
    data.rotL2 = glm::vec3(0.0f, 1.0f, 0.0f);
    data.rotL3 = glm::vec3(0.0f, 0.0f, 1.0f);
    instance.push_back(data);

    _VAO.updateInstances(instance);
    glDrawElements(GL_TRIANGLES, _VAO.nIndices(), GL_UNSIGNED_INT, (void*)0);
    _VAO.deleteInstanceBuffer();

    shader->unbind();
    _VAO.unbind();
}