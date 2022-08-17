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
        Model(MeshData data, GLenum drawtype = GL_STATIC_DRAW){
            VAO.init(data, drawtype);
            animator.init(data);
        }
		//All required uniforms need to be set beforehand from calling class
		void draw(const Shader& shader, Uniforms uniforms){
            const std::vector<glm::mat4> boneMatrices = animator.updateMatrices();
            if (VAO.hasTexture())
                uniforms.flags |= hasTextures;
            uniforms.add_uni("BoneMatrices", boneMatrices);
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

        // const LimbData* getLimbData(const char* name) const {
        //     std::cout << "LIMBS SIZE: " << limbs.size() << std::endl;
        //     for (auto i = 0; i < limbs.size(); ++i){
        //         std::cout << "LIMB: " << limbs[i].name() << std::endl;
        //     }
        //     for (auto i = 0; i < limbs.size(); ++i){
        //         std::cout << "Comparing: " << limbs[i].name() << " with: " << name << std::endl;
        //         if (limbs[i].name() == name)
        //             return &limbs[i];
        //     }
        //     return nullptr;
        // }

        void postTransform(int ID, const glm::mat4& transform) { animator.postTransform(ID, transform); }
        const NodeData* findNode(const char* name) { return animator.findNode(name); }
        void setAnim(int anim) { animator.setAnim(anim); }
        void setLoop(bool loop) { animator.setLoop(loop); }

	private:
		ArrayObject VAO;
		Animator	animator;
};