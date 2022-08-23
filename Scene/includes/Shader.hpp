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

enum shader_type
{
    VERTEX = 0x8B31,
    FRAGMENT = 0x8B30,
    GEOMETRY = 0x8DD9,
};

class Shader {
    public:
		Shader(const char* vertPath, const char* fragPath, const char* geoPath = nullptr);
    
    public:
        //Binds current shader and returns default uniforms
		void bind() const;
        //Exports uniforms to shader
        // void update() const ;
        void update(const Uniforms& uniforms) const;
		void unbind() const;
		void destroy();

    private:
        GLuint compileShader(shader_type type, const char* path);

    public:
		GLuint ID() const;

	private:
        GLuint      _ID;
        Uniforms    _default;
};
