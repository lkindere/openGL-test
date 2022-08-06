#pragma once

#include <vector>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Bone.hpp"
#include "Animator.hpp"
#include "ArrayObject.hpp"

class Model
{
	public:
		Model(const VAOdata& data, const std::vector<Bone>& bonevec, GLenum drawtype = GL_STATIC_DRAW) {
			VAO.init(data.verts, data.indices, drawtype);
			animator.reserve(bonevec.size());
			bones = bonevec;
		}
		//All required uniforms need to be set beforehand from calling class
		void draw(const Shader& shader, const Uniforms& uniforms){
			VAO.bind();
			shader.bind();
			shader.update(uniforms);
			// std::vector<glm::mat4> boneMatrices = animator.updateMatrices(bones);
			// glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "BoneMatrices"),
				// boneMatrices.size(), GL_FALSE, glm::value_ptr(boneMatrices.data()[0]));

			glDrawElements(GL_TRIANGLES, VAO.nIndices(), GL_UNSIGNED_INT, (void*)0);

			shader.unbind();
			VAO.unbind();
		}

		std::vector<Bone>& getbonetemp() { return bones; }

	private:
		ArrayObject			VAO;
		Animator			animator;
		std::vector<Bone>	bones;
};