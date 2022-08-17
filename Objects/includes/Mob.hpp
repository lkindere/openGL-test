#pragma once

#include "Model.hpp"

#include "Weapon.hpp"
#include "Camera.hpp"
#include "settings.hpp"

extern Settings settings;
extern Camera camera;

class Mob
{
	public:
		Mob(Model model);
        
    public:
        void draw(const Shader& shader);
        void move(Uniforms& uni);

	private:
        Model _model;
		Weapon* weapon = nullptr;

    private:
		short health = 10;
		short energy = 10;
        float speed = 0.1;
    
    private:
        // glm::mat4 rotation = glm::mat4(1.0f);
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);

};
