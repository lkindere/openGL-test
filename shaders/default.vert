#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec4 aColor;

out mat4 _camPos;
out vec3 _pos;
out vec3 _normal;
out vec4 _color;
out vec3 _playerPos;

uniform mat4 camPos;
uniform vec3 pos;
uniform vec3 scale;
uniform mat4 rotation;
uniform vec3 playerPos;

void main()
{
	gl_Position = rotation * camPos * vec4((aPos + pos) * scale, 1.0);
	_pos = vec3(pos + aPos);
	_normal = aNorm;
	_color = aColor;
	_camPos = camPos;
	_playerPos = playerPos;
}