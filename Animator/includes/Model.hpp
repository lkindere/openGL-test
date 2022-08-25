#pragma once

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "Structs.hpp"
#include "Shader.hpp"
#include "Animator.hpp"
#include "ArrayObject.hpp"
#include "Hitbox.hpp"

class Model
{
	public:
        Model(MeshData data, GLenum drawtype = GL_STATIC_DRAW);

		void                    draw(const Shader& shader, Uniforms uniforms = Uniforms());
        const NodeData*         findNode(const char* name) const;
        std::vector<glm::mat4>  generateMatrices(const modelIN& input);

        const Hitbox&                   hitbox() const;
        const std::vector<glm::mat4>&   matrices() const;
        float                           duration(int ID) const;

	private:
		ArrayObject _VAO;
		Animator	_animator;
        Hitbox      _hitbox;
};