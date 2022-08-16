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
            limbs = data.limbs;
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

        const glm::mat4& getBoneMatrix(int ID) const {
            return animator.getBoneMatrix(ID);
        }

        const LimbData* getLimbData(const char* name) const {
            for (auto i = 0; i < limbs.size(); ++i){
                if (limbs[i].name == name)
                    return &limbs[i];
            }
            return nullptr;
        }

        void setAnim(int anim){ animator.setAnim(anim); }

	private:
		ArrayObject VAO;
		Animator	animator;
        std::vector<LimbData> limbs;
};