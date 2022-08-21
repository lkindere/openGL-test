#pragma once

#include "Model.hpp"

class Scene;

class Object
{
	public:
		Object(Model model, Scene* scene);
        Object(Model* model, Scene* scene);
        virtual ~Object();

    public:
        void move();
        Uniforms draw(const Shader& shader, Uniforms uni = Uniforms());
        virtual void animate(const Shader& shader, Uniforms uni = Uniforms());

    private:
        bool checkCollision();
        void collisionPhysics(Object& target);

    public:
        const std::string&  name() const ;
        bool                collide() const ;
        unsigned int        shader() const ;
        const glm::vec3&    front() const ;
        const glm::vec3&    position() const ;
        const glm::vec3&    direction() const ;
        const glm::mat4&    rotation() const ;
        const Model&        model() const ;
        const Hitbox&       hitbox() const ;

        void setName(const std::string& name);
        void setCollide(bool b);
        void setShader(unsigned int ID);
        void setFront(const glm::vec3& vec);
        void setFront(float x, float y, float z);
        void setPosition(const glm::vec3& vec);
        void setPosition(float x, float y, float z);
        void setDirection(const glm::vec3& vec);
        void setDirection(float x, float y, float z);
        void setRotation(const glm::mat4& mat);
        void setHitboxPosition(const glm::vec3& vec);
        void setHitboxPosition(float x, float y, float z);
        void setVelocity(const glm::vec3& vec);
        void setVelocity(float x, float y, float z);
        void setWeight(float x);

    protected:
        glm::vec3   _up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3   _front = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3   _position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3   _direction = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::mat4   _rotation = glm::mat4(1.0f);

    protected:
        float       _weight = 0.5f;
        glm::vec3   _velocity = glm::vec3(0.0f);
        
    protected:
        std::string     _name;
        bool            _collide = false;
        unsigned int    _shader = 0;


        Scene*  _scene = nullptr;
		Model   _model;
};
