#pragma once

#include "Structs.hpp"
#include "Shader.hpp"

#include <glad/gl.h>

class Hitbox
{
    public:
        Hitbox(const HitboxData& data);
        void init(HitboxData& data);

        void draw(const Uniforms& uni) const;
        bool checkCollision(const Hitbox& hitbox) const;

    public:
        void setPosition(const glm::vec3& position, const glm::mat4& rotation = glm::mat4(1.0f));
        void setPosition(float x, float y, float z, const glm::mat4& rotation = glm::mat4(1.0f));
    
    private:
        glm::vec3                   _min;
        glm::vec3                   _max;
        glm::vec3                   _position;
        glm::mat3                   _rotation = glm::mat3(1.0f);
};