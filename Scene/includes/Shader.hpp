#pragma once

#include "main.hpp"

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
		void bind() const;
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
