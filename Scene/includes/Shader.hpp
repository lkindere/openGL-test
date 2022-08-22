#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Uniforms.hpp"

class Shader {
    public:
		Shader(const char* vertPath, const char* fragPath, const Uniforms& defaults);
    
    public:
        //Binds current shader and returns default uniforms
		const Uniforms& bind() const;
        //Exports uniforms to shader
        void update() const ;
        void update(const Uniforms& uniforms) const;
		void unbind() const;
		void destroy();

        void setRecalculate(Uniforms (*f) (void)){
            _recalculate = f;
        }

    public:
		GLuint ID() const;

	private:
        GLuint      _ID;
        Uniforms    _default;
        Uniforms (*_recalculate) (void);
};
