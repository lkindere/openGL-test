#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 camPos;
uniform vec3 pos;
uniform vec3 scale;

void main()
{
	gl_Position = camPos * vec4(pos + aPos * scale, 1.0);
}