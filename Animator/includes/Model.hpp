#pragma once

#include <vector>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "Structs.hpp"

#include "Shader.hpp"
#include "Animator.hpp"
#include "ArrayObject.hpp"

#include "settings.hpp"

extern Settings settings;

class Model
{
	public:
        Model(const MeshData& data, GLenum drawtype = GL_STATIC_DRAW){
            VAO.init(data, drawtype);
            animator.init(data);
        }
		//All required uniforms need to be set beforehand from calling class
		void draw(const Shader& shader, Uniforms uniforms){
            const std::vector<glm::mat4> boneMatrices = animator.updateMatrices();
            if (VAO.hasTexture())
                uniforms.flags |= hasTextures;
            uniforms.mat4.insert(make_uni("BoneMatrices", boneMatrices));
			VAO.bind();
			shader.bind();
			shader.update(uniforms);

			glDrawElements(GL_TRIANGLES, VAO.nIndices(), GL_UNSIGNED_INT, (void*)0);

			shader.unbind();
			VAO.unbind();
		}

	private:
		ArrayObject VAO;
		Animator	animator;
};