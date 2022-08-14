#version 330 core

const int hasTexture = 1;

out vec4 FragColor;

in mat4 _camPos;
in vec3 _pos;
in vec3 _normal;
in vec2 _texCoords;
in vec4 _color;

const vec4 ambient = vec4(0.5f);

uniform vec4 lightColor;
uniform vec3 lightPos;

uniform int flags;
uniform sampler2D image;

void main()
{
	vec3 lpos = lightPos;
	vec3 normal = normalize(_normal);
	vec3 lightDir = normalize(lpos - _pos);

	float diffuse = max(dot(_normal, lightDir), 0.0f);

    vec4 texColor = vec4(1.0f);
    if ((flags & hasTexture) != 0)
        texColor = texture(image, _texCoords);
    
	FragColor = _color * lightColor * diffuse + ambient * texColor;
}