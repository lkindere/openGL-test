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
        Model(MeshData data, GLenum drawtype = GL_STATIC_DRAW)
            : _hitbox(data.hitbox) {
            _VAO.init(data, drawtype);
            _animator.init(data);
        }

        ~Model(){
            
        }

		//All required uniforms need to be set beforehand from calling class
		void draw(const Shader& shader, Uniforms uniforms = Uniforms()){
            const std::vector<glm::mat4> boneMatrices = _animator.updateMatrices();
            if (_VAO.hasTexture())
                uniforms.flags |= hasTextures;
            uniforms.add_uni("BoneMatrices", boneMatrices);
			_VAO.bind();
			shader.bind();
			shader.update(uniforms);

			glDrawElements(GL_TRIANGLES, _VAO.nIndices(), GL_UNSIGNED_INT, (void*)0);

			shader.unbind();
			_VAO.unbind();
		}

        const glm::mat4& getBoneMatrix(int ID) const {
            return _animator.getBoneMatrix(ID);
        }
        void postTransform(int ID, const glm::mat4& transform) { _animator.postTransform(ID, transform); }
        const NodeData* findNode(const char* name) { return _animator.findNode(name); }
        void setAnim(int anim) { _animator.setAnim(anim); }
        void setLoop(bool loop) { _animator.setLoop(loop); }


        int anim() const { return _animator.anim(); }
        bool loop() const { return _animator.loop(); }

        void setHitboxPosition(const glm::vec3& position, const glm::mat4& rotation = glm::mat4(1.0f)){
            _hitbox.setPosition(position, rotation);
        }
        
        void setHitboxPosition(float x, float y, float z, const glm::mat4& rotation = glm::mat4(1.0f)){
            _hitbox.setPosition(x, y, z, rotation);
        }

        const Hitbox& hitbox() const { return _hitbox; }

	private:
		ArrayObject _VAO;
		Animator	_animator;
        Hitbox      _hitbox;
};