#pragma once

#include <vector>

#include <glad/gl.h>

#include "Bone.hpp"
#include "ArrayObject.hpp"

class Model
{
	public:
		Model(const VAOdata& data, const std::vector<Bone>& bonevec, GLenum drawtype = GL_STATIC_DRAW) {
			VAO.init(data.verts, data.indices, drawtype);
			bones = bonevec;
		}
		//All required uniforms need to be set beforehand from calling class
		void draw(){
			VAO.bind();
			glDrawElements(GL_TRIANGLES, VAO.nIndices(), GL_UNSIGNED_INT, (void*)0);
			VAO.unbind();
		}

	private:
		ArrayObject			VAO;
		std::vector<Bone>	bones;
		// Animator			animator;
};