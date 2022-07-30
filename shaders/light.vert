#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 camPos;
uniform vec3 pos;

void main()
{
	gl_Position = vec4(pos, 1.0) + camPos * vec4(aPos, 1.0);
}