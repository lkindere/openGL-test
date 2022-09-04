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


struct BoundingBox2D
{
    glm::vec2   _min = glm::vec3(0.0f);
    glm::vec2   _max = glm::vec3(0.0f);

    BoundingBox2D() {};
    BoundingBox2D(const glm::vec2& min, const glm::vec2& max)
        : _min(min), _max(max) {}

    bool contains(const glm::vec3& tmin, const glm::vec3& tmax){
        return (tmin.x >= _min.x && tmax.x <= _max.x)
            && (tmin.z >= _min.y && tmax.z <= _max.y);
    }
};

class Quadtree
{
    BoundingBox2D               _region;
    std::list<Object*>          _objects;
    
    static constexpr float      MIN_SIZE = 1.0f;

    Quadtree*                   _parent = nullptr;
    std::array<Quadtree*, 4>    _children = {nullptr};

    Scene*                      _scene;

    public:
        Quadtree() {}
        Quadtree(const BoundingBox2D& region, const std::list<Object*>& objects, Scene* scene)
            : _region(region), _objects(objects), _scene(scene) {}

        void build(){
            if (_objects.size() <= 1)
                return;
            const glm::vec2& min = _region._min;
            const glm::vec2& max = _region._max;
            glm::vec2 dimensions = max - min;
            if (dimensions.x < MIN_SIZE && dimensions.y < MIN_SIZE)
                return;
            glm::vec2 half = dimensions / glm::vec2(2.0f);
            glm::vec2 center = min + half;
            std::array<BoundingBox2D, 4> quadrants;
            quadrants[0] = BoundingBox2D(min, center);
            quadrants[1] = BoundingBox2D(glm::vec2(min.x, center.y), glm::vec2(center.x, max.y));
            quadrants[2] = BoundingBox2D(glm::vec2(center.x, min.y), glm::vec2(max.x, center.y));
            quadrants[3] = BoundingBox2D(center, max);

            std::array<std::list<Object*>, 4>   quadList;
            std::vector<Object*>                delist;

            for (auto it = _objects.begin(); it != _objects.end(); ++it){
                for (auto i = 0; i < 4; ++i){
                    if (quadrants[i].contains((*it)->HBmin(), (*it)->HBmax())){
                        quadList[i].push_back(*it);
                        delist.push_back(*it);
                        break;
                    }
                }
            }
            for (int i = 0; i < 4; ++i){
                if (quadList[i].size() == 0)
                    continue;
                _children[i] = createNode(quadrants[i], quadList[i]);
                _children[i]->build();
            }
            for (auto i = 0; i < delist.size(); ++i){
                auto it = std::find(_objects.begin(), _objects.end(), delist[i]);
                if (it != _objects.end())
                    _objects.erase(it);
            }
#ifdef DRAW_HITBOXES
            for (auto i = 0; i < 4; ++i)
                draw_box(_scene, glm::vec3(quadrants[i]._min.x, 0.0f, quadrants[i]._min.y), glm::vec3(quadrants[i]._max.x, 5.0f, quadrants[i]._max.y));
#endif
        }

        void checkCollisions(){
            if (_objects.size() != 0){
                for (auto obj = _objects.begin(); obj != _objects.end(); ++obj){
                    if (_objects.size() > 1){
                        for (auto it = _objects.begin(); it != _objects.end(); ++it)
                            (*obj)->checkCollision(**it);
                    }
                    Quadtree* ptr = _parent;
                    while (ptr != nullptr){
                        for (auto it = ptr->_objects.begin(); it != ptr->_objects.end(); ++it)
                            (*obj)->checkCollision(**it);
                        ptr = ptr->_parent;
                    }
                }
            }
            for (auto i = 0; i < 4; ++i){
                if (_children[i] != nullptr)
                    _children[i]->checkCollisions();
            }
        }

    private:
        Quadtree* createNode(const BoundingBox2D& region, std::list<Object*> list){
            Quadtree* tree = new Quadtree(region, list, _scene);
            tree->_parent = this;
            return tree;
        }
};

// struct BoundingBox
// {
//     glm::vec3   _min = glm::vec3(0.0f);
//     glm::vec3   _max = glm::vec3(0.0f);

//     BoundingBox() {};
//     BoundingBox(const glm::vec3& min, const glm::vec3& max)
//         : _min(min), _max(max) {}

//     bool contains(const glm::vec3& tmin, const glm::vec3& tmax){
//         return (tmin.x >= _min.x && tmax.x <= _max.x)
//             && (tmin.y >= _min.y && tmax.y <= _max.y)
//             && (tmin.z >= _min.z && tmax.z <= _max.z);
//     }
// };

// class Octree
// {
//     int                     _level = 0;
//     BoundingBox             _region;
//     std::list<Object*>      _objects;
    
//     const float              MIN_SIZE = 1.0f;

//     Octree*                 _parent = nullptr;
//     std::array<Octree*, 8>  _children = {nullptr};

//     Scene*                  _scene;

//     public:
//         Octree() {}
//         Octree(const BoundingBox& region, const std::list<Object*>& objects, Scene* scene, int level = 0)
//             : _region(region), _objects(objects), _scene(scene), _level(level) {}

//         void build(){
//             if (_objects.size() <= 1)
//                 return;
//             const glm::vec3& min = _region._min;
//             const glm::vec3& max = _region._max;
//             glm::vec3 dimensions = max - min;
//             if (dimensions.x < MIN_SIZE && dimensions.y < MIN_SIZE && dimensions.z < MIN_SIZE)  
//                 return;
//             glm::vec3 half = dimensions / glm::vec3(2.0f);
//             glm::vec3 center = min + half;
//             std::array<BoundingBox, 8> octants;
//             octants[0] = BoundingBox(min, center);
//             octants[1] = BoundingBox(glm::vec3(min.x, center.y, min.z), glm::vec3(center.x, max.y, center.z));
//             octants[2] = BoundingBox(glm::vec3(min.x, min.y, center.z), glm::vec3(center.x, center.y, max.z));
//             octants[3] = BoundingBox(glm::vec3(center.x, min.y, min.z), glm::vec3(max.x, center.y, center.z));
//             octants[4] = BoundingBox(center, max);
//             octants[5] = BoundingBox(glm::vec3(center.x, center.y, min.z), glm::vec3(max.x, max.y, center.z));
//             octants[6] = BoundingBox(glm::vec3(center.x, min.y, center.z), glm::vec3(max.x, center.y, max.z));
//             octants[7] = BoundingBox(glm::vec3(min.x, center.y, center.z), glm::vec3(center.x, max.y, max.z));

//             std::array<std::list<Object*>, 8>   octList;
//             std::vector<Object*>                delist;

//             for (auto it = _objects.begin(); it != _objects.end(); ++it){
//                 for (auto i = 0; i < 8; ++i){
//                     if (octants[i].contains((*it)->HBmin(), (*it)->HBmax())){
//                         octList[i].push_back(*it);
//                         delist.push_back(*it);
//                         break;
//                     }
//                 }
//             }
//             for (int i = 0; i < 8; ++i){
//                 if (octList[i].size() == 0)
//                     continue;
//                 _children[i] = createNode(octants[i], octList[i]);
//                 _children[i]->build();
//             }
//             for (auto i = 0; i < delist.size(); ++i){
//                 auto it = std::find(_objects.begin(), _objects.end(), delist[i]);
//                 if (it != _objects.end())
//                     _objects.erase(it);
//             }
//             for (auto i = 0; i < 8; ++i)
//                 draw_box(_scene, octants[i]._min, octants[i]._max);
//         }

//         void checkCollisions(){
//             if (_objects.size() != 0){
//                 for (auto obj = _objects.begin(); obj != _objects.end(); ++obj){
//                     if (_objects.size() > 1){
//                         for (auto it = _objects.begin(); it != _objects.end(); ++it)
//                             (*obj)->checkCollision(**it);
//                     }
//                     Octree* ptr = _parent;
//                     while (ptr != nullptr){
//                         for (auto it = ptr->_objects.begin(); it != ptr->_objects.end(); ++it)
//                             (*obj)->checkCollision(**it);
//                         ptr = ptr->_parent;
//                     }
//                 }
//             }
//             for (auto i = 0; i < 8; ++i){
//                 if (_children[i] != nullptr)
//                     _children[i]->checkCollisions();
//             }
//         }

//         Octree* createNode(const BoundingBox& region, std::list<Object*> list){
//             Octree* tree = new Octree(region, list, _scene, _level + 1);
//             tree->_parent = this;
//             return tree;
//         }
// };
