#pragma once

#include "Structs.hpp"

struct Uniforms;
class Object;

class Hitbox
{
    public:
        Hitbox(const HitboxData& data);

        void draw(const Uniforms& uni) const;
        bool checkCollision(const Object& obj, const Object& target) const;
    
    private:
        std::pair<glm::vec3, glm::vec3>  findCollision(const glm::vec3& min, const glm::vec3& max, const glm::vec3& min2, const glm::vec3& max2) const;
    
    private:
        glm::vec3                   _min;
        glm::vec3                   _max;
        glm::mat3                   _rotation = glm::mat3(1.0f);
};