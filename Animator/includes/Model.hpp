#pragma once

#include "main.hpp"

#include "Shader.hpp"
#include "Animator.hpp"
#include "ArrayObject.hpp"
#include "Hitbox.hpp"

class Model
{
	public:
        Model(MeshData data, int ID, GLenum drawtype = GL_STATIC_DRAW);

		void                    draw(const Shader& shader, Uniforms uniforms = Uniforms());
        void                    buffer(const InstanceData& instance);
        void                    clearBuffer();
        const NodeData*         findNode(const char* name) const;
        std::vector<glm::mat4>  generateMatrices(const modelIN& input);

        const std::vector<glm::vec3>&   hitboxBase() const;
        const std::vector<glm::mat4>&   matrices() const;
        float                           duration(int ID) const;

        int                             ID() const { return _ID; }

	private:
        int                         _ID;
		ArrayObject                 _VAO;
        std::vector<InstanceData>   _instances;
		Animator                    _animator;
        std::vector<glm::vec3>      _hitboxBase;
};