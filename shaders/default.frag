#version 330 core

out vec4 FragColor;

in vec3 _pos;
in vec3 _normal;
in vec3 _color;

uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
	vec3 normal = normalize(_normal);
	vec3 lightDir = normalize(lightPos - _pos);

	float diffuse = max(dot(_normal, lightDir), 0.0f);

	FragColor = vec4(_color, 1.0f) * lightColor * diffuse + vec4(0.1);
}