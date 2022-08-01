#version 330 core

out vec4 FragColor;

in mat4 _camPos;
in vec3 _pos;
in vec3 _normal;
in vec4 _color;
in vec3 _playerPos;

uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
	// vec3 lpos = (_camPos * vec4(1.0f)).xyz;
	vec3 lpos = lightPos;
	vec3 normal = normalize(_normal);
	vec3 lightDir = normalize(lpos - _pos);

	float diffuse = max(dot(_normal, lightDir), 0.0f);

	FragColor = vec4(_color) * lightColor * diffuse;
}