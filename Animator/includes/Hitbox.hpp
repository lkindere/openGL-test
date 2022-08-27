#pragma once

#include "Structs.hpp"

struct Uniforms;
class Object;

struct CollisionData
{
    glm::vec3 distance1;
    glm::vec3 distance2;
    bool hit = false;
};

class Hitbox
{
    public:
        Hitbox(const HitboxData& data);

        void draw(const Uniforms& uni) const;
        CollisionData checkCollision(const Object& obj, const Object& target) const;
    
    private:
        CollisionData findCollision(const glm::vec3& min, const glm::vec3& max, const glm::vec3& min2, const glm::vec3& max2) const;
    
    private:
        glm::vec3                   _min;
        glm::vec3                   _max;
        glm::mat3                   _rotation = glm::mat3(1.0f);
};