#include "Shader.hpp"

#ifdef DEBUG
#include <iostream>
#endif

Shader::Shader(const char* vertPath, const char* fragPath) {
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

#ifdef DEBUG
    GLint status;
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
    std::cout << "\nVert shader compiled: " << (status == GL_TRUE) << '\n';
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
    std::cout << "\nFrag shader compiled: " << (status == GL_TRUE) << '\n'
              << std::endl;
#endif

    ID = glCreateProgram();
    glAttachShader(ID, vertShader);
    glAttachShader(ID, fragShader);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    glLinkProgram(ID);
}

void Shader::activate() { glUseProgram(ID); }
void Shader::destroy() { glDeleteProgram(ID); }
GLuint Shader::getID() { return ID; }