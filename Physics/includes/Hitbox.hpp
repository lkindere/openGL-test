#pragma once

#include "Structs.hpp"
#include "Shader.hpp"

#include <glad/gl.h>

class Hitbox
{
    public:
        Hitbox();
        void init(HitboxData& data);

        void updateHitbox(const glm::mat4& transformation);

        void draw(const Shader& shader, Uniforms uniforms) const;
        bool checkCollision(const Hitbox& hitbox) const;
    
    private:
        std::vector<glm::vec3>      _vertices;
        glm::mat4                   _transformation = glm::mat4(1.0f);
};