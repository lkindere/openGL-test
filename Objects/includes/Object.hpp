#pragma once

#include <memory>

#include "Enums.hpp"
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
        virtual void animate(int ID, bool loop);
        virtual void loop();
        virtual void animLoop();
        virtual void damage(short dmg);
        void recalculateHitbox();

    protected:
        virtual void setDefaultUniforms();

    private:
        void checkCollision();
        void collisionPhysics(Object& target, CollisionData& data);

    public:
        int                 ID() const;
        const std::string&  name() const;
        object_type         type() const;
        bool                collide() const;
        bool                isInstanced() const;
        bool                isStatic() const;
        bool                animating() const;

        int                 shader() const;
        int                 flags() const;

        const glm::vec3&    front() const;
        const glm::vec3&    direction() const;
        const glm::vec3&    position() const;
        const glm::vec3&    velocity() const;
        glm::vec3           finalpos() const;
        const glm::vec3&    scale() const;
        const glm::mat4&    rotation() const;
        const Hitbox&       hitbox() const;
        Hitbox&             hitbox();


        const std::shared_ptr<Model>& model() const;

        void setName(const std::string& name);
        void setType(object_type type);
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
        Uniforms    _uniforms;
        int         _shader = 0;
        int         _flags = 0;

    protected:
        bool        _animating = false;
        bool        _newRotation = false;
        float       _aStart = 0.0f;
        float       _aDuration = 0.0f;

    protected:
        object_info             _info;
        Scene*                  _scene = nullptr;
        
        Hitbox                  _hitbox;
		std::shared_ptr<Model>  _model;
        modelIN                 _mdata;
};