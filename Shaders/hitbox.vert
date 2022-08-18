#version 330 core

layout (location = 0) in vec3 aModel;

uniform vec3 pos;
uniform mat4 camPos;

void main()
{
	vec4 model = vec4(pos + aModel, 1.0f);
    gl_Position = camPos * model;
}