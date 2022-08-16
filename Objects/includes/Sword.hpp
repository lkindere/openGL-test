#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ArrayObject.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Weapon.hpp"

#include "settings.hpp"

extern Settings settings;
extern Camera camera;

#include <unistd.h>

class Sword : public Weapon
{		//
	public:
		Sword(const Model& model)
			: _model(model) {}

		void draw(Shader& shader, const glm::vec3& pos){
			// glm::vec3 scale(0.01f);
			// glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(camera.yaw()), glm::vec3(0.0f, 1.0f, 0.0f));
			// glm::vec3 drawpos = pos + dir;
            // glm::vec4 drawpos = bone * glm::vec4(pos, 1.0f);

			Uniforms uni;
			uni.vec3 = {
				// make_uni("fOffset", glm::vec3(0.5f, -0.5f, 0.0f)),
				make_uni("pos", pos),
				make_uni("scale", glm::vec3(1.0f))
			};
			uni.mat4 = {
                // make_uni("rotation", rotation),
                make_uni("camPos", camera.matrix())
			};
			_model.draw(shader, uni);
		}
	private:
		const short damage = 10;
		const short range = 10;
		const short speed = 10;
		Model _model;
};