#include "Shader.hpp"

GLuint Shader::compileShader(shader_type type, const char* path){
    std::ifstream input(path);
    std::stringstream sstream;
    sstream << input.rdbuf();
    std::string str(sstream.str());
    const GLchar* data = str.c_str();
    GLuint ID = glCreateShader(type);
    glShaderSource(ID, 1, &data, NULL);
    glCompileShader(ID);
    return ID;
}

Shader::Shader(const char* vertPath, const char* fragPath, const char* geoPath) {
    _ID = glCreateProgram();

    GLuint vert = compileShader(VERTEX, vertPath);
    GLuint frag = compileShader(FRAGMENT, fragPath);
    if (geoPath){
        GLuint geo = compileShader(GEOMETRY, geoPath);
        glAttachShader(_ID, geo);
        glDeleteShader(geo);
    }
    glAttachShader(_ID, vert);
    glAttachShader(_ID, frag);
    glDeleteShader(frag);
    glDeleteShader(vert);

    glLinkProgram(_ID);
}

void Shader::bind() const {
	glUseProgram(_ID);
}

//Exports provided uniforms to shader or defaults if not specified
void Shader::update(const Uniforms& uniforms) const {
    glUniform1i(glGetUniformLocation(_ID, "flags"), uniforms.flags);
    for (auto it = uniforms.f1.begin(); it != uniforms.f1.end(); ++it)
		glUniform1f(glGetUniformLocation(_ID, it->first), it->second);
	for (auto it = uniforms.vec3.begin(); it != uniforms.vec3.end(); ++it)
		glUniform3fv(glGetUniformLocation(_ID, it->first), it->second.size(), glm::value_ptr(it->second.data()[0]));
	for (auto it = uniforms.vec4.begin(); it != uniforms.vec4.end(); ++it)
		glUniform4fv(glGetUniformLocation(_ID, it->first), it->second.size(), glm::value_ptr(it->second.data()[0]));
	for (auto it = uniforms.mat4.begin(); it != uniforms.mat4.end(); ++it)
		glUniformMatrix4fv(glGetUniformLocation(_ID, it->first), it->second.size(), GL_FALSE, glm::value_ptr(it->second.data()[0]));
}

void Shader::unbind() const { glUseProgram(0); }
void Shader::destroy() { glDeleteProgram(_ID); }
GLuint Shader::ID() const { return _ID; }