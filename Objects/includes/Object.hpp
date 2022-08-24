#pragma once

#include <memory>

#include "Model.hpp"
#include "Hitbox.hpp"

class Scene;

class Object
{
	public:
        //Unique instancing
		Object(MeshData data, Scene* scene, int ID);
        Object(MeshData* data, Scene* scene, int ID);
        // Shared model instancing
        Object(const std::shared_ptr<Model>& modelptr, Scene* scene, int ID);
        virtual ~Object();

    public:
        void move();
        void draw();
        virtual void animate();
        virtual void damage(short dmg);

    protected:
        virtual void setDefaultUniforms();

    private:
        bool checkCollision();
        void collisionPhysics(Object& target);

    public:
        int                 ID() const ;
        const std::string&  name() const ;
        bool                collide() const ;
        int                 shader() const ;
        int                 flags() const;
        const glm::vec3&    front() const ;
        const glm::vec3&    position() const ;
        const glm::vec3&    direction() const ;
        const glm::vec3&    scale() const ;
        const glm::mat4&    rotation() const ;
        const Hitbox&       hitbox() const ;

        const std::shared_ptr<Model>& model() const ;

        void setName(const std::string& name);
        void setCollide(bool b);
        void setShader(int ID);
        void setFlags(int flags);
        void setFront(const glm::vec3& vec);
        void setFront(float x, float y, float z);
        void setPosition(const glm::vec3& vec);
        void setPosition(float x, float y, float z);
        void setDirection(const glm::vec3& vec);
        void setDirection(float x, float y, float z);
        void setScale(const glm::vec3& vec);
        void setScale(float x, float y, float z);
        void setRotation(const glm::mat4& mat);
        void setVelocity(const glm::vec3& vec);
        void setVelocity(float x, float y, float z);
        void setWeight(float x);

    protected:
        glm::vec3   _up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3   _front = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3   _position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3   _direction = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3   _scale = glm::vec3(1.0f);
        glm::mat4   _rotation = glm::mat4(1.0f);

    protected:
        float       _weight = 0.5f;
        glm::vec3   _velocity = glm::vec3(0.0f);
        
    protected:
        int _shader = 0;
        int _flags = 0;

    protected:
        int             _ID;
        std::string     _name;
        bool            _collide = false;

        Scene*      _scene = nullptr;
        Uniforms    _uniforms;

		std::shared_ptr<Model>  _model;
};
