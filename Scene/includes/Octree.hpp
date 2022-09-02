#pragma once

#include "Scene.hpp"

extern Shader* g_hitboxShader;

void draw_box(const Scene* scene, const glm::vec3& min, const glm::vec3& max)
{
    Uniforms uni;
    uni.flags = 0;
    uni.add_uni("pos", glm::vec3(0.0f));
    uni.add_uni("camPos", scene->camera().matrix());
    uni.add_uni("scale", glm::vec3(1.0f));
    uni.add_uni("rotation", glm::mat4(1.0f));
    std::vector<glm::vec3> vertices = {
        min,                                //0
        glm::vec3(min.x, min.y, max.z),     //1
        glm::vec3(min.x, max.y, min.z),     //2
        glm::vec3(max.x, min.y, min.z),     //3

        glm::vec3(max.x, min.y, max.z),     //4
        glm::vec3(max.x, max.y, min.z),     //5
        glm::vec3(min.x, max.y, max.z),     //6
        max,                                //7
    };
    std::vector<GLuint> indices = {
        0, 1, 0, 2, 0, 3,
        7, 6, 7, 5, 7, 4,
        1, 6, 1, 4,
        5, 2, 5, 3,
        3, 4, 2, 6,
    };
    g_hitboxShader->bind();
    g_hitboxShader->update(uni);

    GLuint temp;
    glGenVertexArrays(1, &temp);
	glBindVertexArray(temp);

    GLuint VerticeBuffer;
	glGenBuffers(1, &VerticeBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VerticeBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STREAM_DRAW);

	GLuint IndiceBuffer;
	glGenBuffers(1, &IndiceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndiceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STREAM_DRAW);

    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, (void*)0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDeleteBuffers(1, &VerticeBuffer);
    glDeleteBuffers(1, &IndiceBuffer);
    glDeleteVertexArrays(1, &temp);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    g_hitboxShader->unbind();
}

struct BoundingBox
{
    glm::vec3   _min = glm::vec3(0.0f);
    glm::vec3   _max = glm::vec3(0.0f);

    BoundingBox() {};
    BoundingBox(const glm::vec3& min, const glm::vec3& max)
        : _min(min), _max(max) {}

    //Need to rework to min/max checks if inconsistent
    bool contains(const glm::vec3& pos){
        return (pos.x >= _min.x && pos.x <= _max.x
            &&  pos.z >= _min.z && pos.z <= _max.z
            &&  pos.y >= _min.y && pos.y <= _max.y);
    }
};

class Octree
{
    BoundingBox             _region;
    std::list<Object*>      _objects;
    
    const float              MIN_SIZE = 1.0f;

    Octree*                 _parent = nullptr;
    std::array<Octree*, 8>  _children;

    Scene*                  _scene;

    public:
        Octree() {}
        Octree(const BoundingBox& region, const std::list<Object*>& objects, Scene* scene)
            : _region(region), _objects(objects), _scene(scene) {}

        void build(){
            if (_objects.size() <= 1)
                return;
            const glm::vec3& min = _region._min;
            const glm::vec3& max = _region._max;
            glm::vec3 dimensions = max - min;
            if (dimensions.x < MIN_SIZE && dimensions.y < MIN_SIZE && dimensions.z < MIN_SIZE)  
                return;
            glm::vec3 half = dimensions / glm::vec3(2.0f);
            glm::vec3 center = min + half;
            std::array<BoundingBox, 8> octants;
            octants[0] = BoundingBox(min, center);
            octants[1] = BoundingBox(glm::vec3(min.x, center.y, min.z), glm::vec3(center.x, max.y, center.z));
            octants[2] = BoundingBox(glm::vec3(min.x, min.y, center.z), glm::vec3(center.x, center.y, max.z));
            octants[3] = BoundingBox(glm::vec3(min.x, center.y, center.z), glm::vec3(center.x, max.y, max.z));
            octants[4] = BoundingBox(center, max);
            octants[5] = BoundingBox(glm::vec3(center.x, center.y, min.z), glm::vec3(max.x, max.y, center.z));
            octants[6] = BoundingBox(glm::vec3(center.x, min.y, center.z), glm::vec3(max.x, center.y, max.z));
            octants[7] = BoundingBox(glm::vec3(center.x, center.y, center.z), glm::vec3(max.x, max.y, max.z));

            std::array<std::list<Object*>, 8>   octList;
            std::vector<Object*>                delist;

            for (auto it = _objects.begin(); it != _objects.end(); ++it){
                if ((*it)->collide() == false)
                    continue;
                // std::cout << "Iterating" << std::endl;
                for (auto i = 0; i < 8; ++i){
                    if (octants[i].contains((*it)->finalpos())){
                        // std::cout << "Contains" << std::endl;
                        octList[i].push_back(*it);
                        delist.push_back(*it);
                        break;
                    }
                }
            }

            for (int i = 0; i < 8; ++i){
                if (octList[i].size() == 0)
                    continue;
                // std::cout << "Octlist[" << i << "] size: " << octList[i].size() << std::endl;
                _children[i] = createNode(octants[i], octList[i]);
                _children[i]->build();
            }

            //Remove delists from objects
            for (auto i = 0; i < delist.size(); ++i){
                auto it = std::find(_objects.begin(), _objects.end(), delist[i]);
                if (it != _objects.end())
                    _objects.erase(it);
            }


            std::cout << "Node contains: " << _objects.size() << std::endl;
            Octree* ptr = _parent;
            int i = 0;
            while (ptr){
                ptr = ptr->_parent;
                ++i;
            }
            std::cout << "Level: " << i << std::endl;
            for (auto i = 0; i < 8; ++i)
                draw_box(_scene, octants[i]._min, octants[i]._max);
        }



        Octree* createNode(const BoundingBox& region, std::list<Object*> list){
            Octree* tree = new Octree(region, list, _scene);
            tree->_parent = this;
            return tree;
        }
};
