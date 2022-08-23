#version 330 core

const int hasTexture = 1;

const vec4 ambient = vec4(0.3f);

uniform int flags;
uniform mat4 camPos;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform sampler2D image;

in data
{
    vec3 pos;
    vec3 normal;
    vec4 color;
    vec2 texCoords;
} data_in;

out vec4 FragColor;

void main()
{
	vec3 lpos = lightPos;
	vec3 normal = normalize(data_in.normal);
	vec3 lightDir = normalize(lpos - data_in.pos);

	float diffuse = max(dot(data_in.normal, lightDir), 0.0f);

    vec4 texColor = vec4(1.0f);
    if ((flags & hasTexture) != 0)
        texColor = texture(image, data_in.texCoords);
    
	FragColor = data_in.color * lightColor * diffuse + ambient * texColor;
}