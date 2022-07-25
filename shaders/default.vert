#version 330 core

//Position
layout (location = 0) in vec3 aPos;
//Normal
layout (location = 1) in vec3 aNormal;
//Color
layout (location = 2) in vec3 aColor;

//Outputs for fragment shader
out vec3 _position;
out vec3 _normal;
out vec3 _color;

uniform mat4 camMatrix;

void main()
{
	_position = vec3(model * vec4(aPos, 1.0f));
	_color = aColor;
	_normal = aNormal;
	gl_Position = camMatrix * vec4(aPos, 1.0);
}