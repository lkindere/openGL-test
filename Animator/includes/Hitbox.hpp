#pragma once

#include "main.hpp"

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
        Hitbox();
        void draw(const Uniforms& uni);
        CollisionData   checkCollision(Object& obj, Object& target);
        void            recalculate(const std::vector<glm::vec3>& base, const glm::mat3& rotation);
    
    private:
        void            getNormals();
        CollisionData   checkY(float finalY, float tfinalY, const Object& obj, const Object& target) const;
        CollisionData   sat2D(Object& obj, Object& target);
        CollisionData   checkDirection(const glm::vec3& finalpos, const glm::vec3& tfinalpos, CollisionData& data) const;
        glm::vec2       getMinMax(const glm::vec2& normal, const Object& obj) const;
        float           getOverlap(const glm::vec2& minMax, const glm::vec2& tminMax) const;

    public:
        const glm::vec3& min() const { return _min; }
        const glm::vec3& max() const { return _max; }
    
    private:
        std::vector<glm::vec3>  _vertices;
        glm::vec3               _min;
        glm::vec3               _max;
        std::vector<glm::vec2>  _flats;
        std::vector<glm::vec2>  _normals;
};