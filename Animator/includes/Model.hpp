#pragma once

#include "main.hpp"

#include "Shader.hpp"
#include "Animator.hpp"
#include "ArrayObject.hpp"
#include "Hitbox.hpp"

class Scene;

struct BufferData
{
    const std::vector<glm::mat4>&   bones;
    int                             firstInsertion = -1;
    BufferData(const std::vector<glm::mat4>& vec, int first)
        : bones(vec), firstInsertion(first) {}
};

class Model
{
	public:
        Model(MeshData data, int ID, int shader, Scene* scene);

		void                    draw(Uniforms uniforms = Uniforms());
        BufferData              buffer(const InstanceData& instance, const modelIN& in);
        void                    clearBuffer();
        const NodeData*         findNode(const char* name) const;
        std::vector<glm::mat4>  generateMatrices(const modelIN& input);

        const std::vector<glm::vec3>&   hitboxBase() const;
        const std::vector<glm::mat4>&   matrices() const;
        float                           duration(int ID) const;

        int                             ID() const { return _ID; }
        int                             shader() const { return _shaderID; }
        void                            setShader(int shader) { _shaderID = shader; }

	private:
        Scene*                          _scene;
        int                             _ID;
        int                             _shaderID;

        int                             _flags = 0;
		ArrayObject                     _VAO;
		Animator                        _animator;
        std::vector<InstanceData>       _instances;
        std::vector<glm::mat4>          _instanceBones;
        std::vector<glm::vec3>          _hitboxBase;

};