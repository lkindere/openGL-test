#pragma once

#include "settings.hpp"
#include "Camera.hpp"
#include "Model.hpp"

extern Settings settings;
extern Camera camera;

class Object
{
	public:
		Object(Model model);
        Object(Model* model);
        virtual ~Object();

    public:
        Uniforms draw(const Shader& shader, Uniforms uni = Uniforms());

    public:
        const glm::vec3&    front() const ;
        const glm::vec3&    position() const ;
        const glm::vec3&    direction() const ;
        const glm::mat4&    rotation() const ;
        const Model&        model() const ;

        void setFront(const glm::vec3& vec);
        void setFront(float x, float y, float z);
        void setPosition(const glm::vec3& vec);
        void setPosition(float x, float y, float z);
        void setDirection(const glm::vec3& vec);
        void setDirection(float x, float y, float z);
        void setRotation(const glm::mat4& mat);

    protected:
        glm::vec3 _front = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 _direction = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::mat4 _rotation = glm::mat4(1.0f);
        
    protected:
		Model _model;
};
