#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <glad/gl.h>
#include <GLFW/glfw3.h>

struct Uniforms {
    std::map<std::string, glm::vec3>    vec3;
    std::map<std::string, glm::vec4>    vec4;
    std::map<std::string, glm::mat4>    mat4;
};

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

    public:
		GLuint ID() const;

	private:
        GLuint      _ID;
        Uniforms    _default;
};
