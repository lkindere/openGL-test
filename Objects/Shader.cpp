#include "Shader.hpp"

#ifdef DEBUG
#include <iostream>
#endif

Shader::Shader(const char* vertPath, const char* fragPath, const Uniforms& defaults) {
    // Read and convert to usable format
    std::ifstream vertStream(vertPath), fragStream(fragPath);
    std::stringstream vertData, fragData;
    vertData << vertStream.rdbuf();
    fragData << fragStream.rdbuf();
    std::string f = fragData.str();
    std::string v = vertData.str();
    const GLchar* frag = f.c_str();
    const GLchar* vert = v.c_str();

    // Compile shaders and link ID
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertShader, 1, &vert, NULL);
    glShaderSource(fragShader, 1, &frag, NULL);
    glCompileShader(vertShader);
    glCompileShader(fragShader);
	_default = defaults;

#ifdef DEBUG
    GLint status;
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
    std::cout << "\nVert shader compiled: " << (status == GL_TRUE) << '\n';
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
    std::cout << "\nFrag shader compiled: " << (status == GL_TRUE) << '\n'
              << std::endl;
#endif

    _ID = glCreateProgram();
    glAttachShader(_ID, vertShader);
    glAttachShader(_ID, fragShader);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    glLinkProgram(_ID);
}

const Uniforms& Shader::bind() const {
	glUseProgram(_ID);
	return _default;
}

//Exports provided uniforms to shader or defaults if not specified
void Shader::update(const Uniforms& uniforms) const {
    for (auto dit = _default.int1.begin(); dit != _default.int1.end(); ++dit){
		auto it = uniforms.int1.find(dit->first);
		(it != uniforms.int1.end()) ?
			glUniform1iv(glGetUniformLocation(_ID, it->first), it->second.size(), it->second.data())
			:	glUniform1iv(glGetUniformLocation(_ID, dit->first), dit->second.size(), dit->second.data());
	}
	for (auto dit = _default.vec3.begin(); dit != _default.vec3.end(); ++dit){
		auto it = uniforms.vec3.find(dit->first);
		(it != uniforms.vec3.end()) ?
			glUniform3fv(glGetUniformLocation(_ID, it->first), it->second.size(), glm::value_ptr(it->second.data()[0]))
			:	glUniform3fv(glGetUniformLocation(_ID, dit->first), dit->second.size(), glm::value_ptr(dit->second.data()[0]));
	}
	for (auto dit = _default.vec4.begin(); dit != _default.vec4.end(); ++dit){
		auto it = uniforms.vec4.find(dit->first);
		(it != uniforms.vec4.end()) ?
			glUniform4fv(glGetUniformLocation(_ID, it->first), it->second.size(), glm::value_ptr(it->second.data()[0]))
			:	glUniform4fv(glGetUniformLocation(_ID, dit->first), dit->second.size(), glm::value_ptr(dit->second.data()[0]));
	}
	for (auto dit = _default.mat4.begin(); dit != _default.mat4.end(); ++dit){
		auto it = uniforms.mat4.find(dit->first);
		(it != uniforms.mat4.end()) ?
			glUniformMatrix4fv(glGetUniformLocation(_ID, it->first), it->second.size(), GL_FALSE, glm::value_ptr(it->second.data()[0]))
			:	glUniformMatrix4fv(glGetUniformLocation(_ID, dit->first), dit->second.size(), GL_FALSE, glm::value_ptr(dit->second.data()[0]));
	}
}

//Exports default uniforms to shader
void Shader::update() const {
    for (auto dit = _default.int1.begin(); dit != _default.int1.end(); ++dit)
        glUniform1iv(glGetUniformLocation(_ID, dit->first), dit->second.size(), dit->second.data());
	for (auto dit = _default.vec3.begin(); dit != _default.vec3.end(); ++dit)
		glUniform3fv(glGetUniformLocation(_ID, dit->first), dit->second.size(), glm::value_ptr(dit->second.data()[0]));
	for (auto dit = _default.vec4.begin(); dit != _default.vec4.end(); ++dit)
		glUniform4fv(glGetUniformLocation(_ID, dit->first), dit->second.size(), glm::value_ptr(dit->second.data()[0]));
	for (auto dit = _default.mat4.begin(); dit != _default.mat4.end(); ++dit)
		glUniformMatrix4fv(glGetUniformLocation(_ID, dit->first), dit->second.size(), GL_FALSE, glm::value_ptr(dit->second.data()[0]));
}

void Shader::unbind() const { glUseProgram(0); }
void Shader::destroy() { glDeleteProgram(_ID); }
GLuint Shader::ID() const { return _ID; }