#pragma once

#include "Structs.hpp"
#include "Shader.hpp"

#include <glad/gl.h>

class Hitbox
{
    public:
        Hitbox();
        void init(HitboxData& data);

        // void updateHitbox(const glm::mat4& transformation);

        void draw(const Shader& shader, Uniforms uniforms) const;
        bool checkCollision(const Hitbox& hitbox) const;

    public:
        void setPosition(const glm::vec3& position);
        void setPosition(float x, float y, float z);
    
    private:
        glm::vec3                   _min;
        glm::vec3                   _max;
        glm::vec3                   _position;
};