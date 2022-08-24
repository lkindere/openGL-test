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
        glm::vec3                   _min;
        glm::vec3                   _max;
        glm::mat3                   _rotation = glm::mat3(1.0f);
};