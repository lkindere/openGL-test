#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 _color;

uniform mat4 camPos;
uniform mat4 rotation;
uniform vec3 pos;

void main()
{
	gl_Position = vec4(pos, 1.0) + camPos * rotation * vec4(aPos, 1.0);
	_color = aColor;
}