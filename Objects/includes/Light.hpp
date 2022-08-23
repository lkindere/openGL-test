#pragma once

#include "Object.hpp"

class Light : public Object
{
	public:
		Light(MeshData data, Scene* scene);

    public:
		void addTarget(Shader& target);
        void animate();

    private:
        void setDefaultUniforms();

	private:
		std::vector<Shader>	_targets;
		glm::vec4 _color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};
