#version 330 core

layout (location = 0) in vec3 aModel;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aTextures;
layout (location = 4) in ivec3 aBones;
layout (location = 5) in vec3 aWeights;

//Instance
layout (location = 6) in vec3 iPos;

uniform mat4 camPos;

out vec2 _texCoords;

void main()
{
	gl_Position = camPos * vec4(iPos + aModel, 1.0);
    _texCoords = aTextures;
}