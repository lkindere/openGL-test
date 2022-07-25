#version 330 core

out vec4 FragColor;

//Input from vertex shader
in vec3 _position;
in vec3 _normal;
in vec3 _color;

uniform vec4 lightColor;

void main()
{
	FragColor = vec4(color, 1.0f) * lightColor;
}