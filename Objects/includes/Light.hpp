#pragma once

#include "Object.hpp"

class Light : public Object
{
	public:
		Light(Model model);

    public:
		void addTarget(Shader& target);
        void animate(Shader& target);

	private:
		std::vector<Shader>	_targets;
		glm::vec4 _color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};
