#pragma once

#include "Structs.hpp"

struct Uniforms;
class Object;

struct CollisionData
{
    float       overlap;
    glm::vec3   normal;
};

class Hitbox
{
    public:
        Hitbox(const HitboxData& data);
        void draw(const Uniforms& uni);
        void setRotation(const glm::mat4& mat);
        CollisionData checkCollision(const Object& obj, const Object& target) const;
    
    private:
        void            recalculate(const std::vector<glm::vec3>& vertices);
        glm::vec2       get2Dnormal(const glm::vec2& p1, const glm::vec2& p2) const;
        CollisionData   checkY(float finalY, float tfinalY, const Object& obj, const Object& target) const;
        CollisionData   sat2D(const Object& obj, const Object& target) const;
        CollisionData   checkDirection(const glm::vec3& finalpos, const glm::vec3& tfinalpos, CollisionData& data) const;
        glm::vec2       getMinMax(const glm::vec2& normal, const Object& obj) const;
        float           getOverlap(const glm::vec2& minMax, const glm::vec2& tminMax) const;
    
    private:
        std::vector<glm::vec3>  _vertices;
        float                   _minY;
        float                   _maxY;
        std::vector<glm::vec2>  _flats;
        std::vector<glm::vec2>  _normals;
        glm::mat2               _rot = glm::mat2(1.0f);
};