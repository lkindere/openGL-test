#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 _color;

uniform mat4 camPos;

void main()
{
   gl_Position = camPos * vec4(aPos, 1.0);
   _color = aColor;
}