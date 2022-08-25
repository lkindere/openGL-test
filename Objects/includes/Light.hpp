#pragma once

#include "Object.hpp"

class Light : public Object
{
	public:
		Light(MeshData data, Scene* scene, int ID);
        Light(const std::shared_ptr<Model>& modelptr, Scene* scene, int ID);

    public:
        void loop();

    private:
        void setDefaultUniforms();

	private:
		glm::vec4 _color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};
