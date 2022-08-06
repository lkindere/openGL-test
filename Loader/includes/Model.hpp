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
		void draw(const Shader& shader, Uniforms uniforms){
			std::vector<glm::mat4> boneMatrices = animator.updateMatrices(bones);
            uniforms.mat4.insert(make_uni("BoneMatrices", boneMatrices));
			VAO.bind();
			shader.bind();
			shader.update(uniforms);

			glDrawElements(GL_TRIANGLES, VAO.nIndices(), GL_UNSIGNED_INT, (void*)0);

			shader.unbind();
			VAO.unbind();
		}

	private:
		ArrayObject			VAO;
		Animator			animator;
		std::vector<Bone>	bones;
};