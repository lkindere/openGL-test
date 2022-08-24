#version 330 core

//Flags
const int hasTexture = 1;
const int deformOn = 2;

const vec4 ambient = vec4(0.3f, 0.3f, 0.3f, 1.0f);

uniform int flags;
uniform float uTime;
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
    vec4 color = data_in.color;
    vec4 texColor = vec4(1.0f);

    if ((flags & hasTexture) != 0)
        texColor = texture(image, data_in.texCoords);
    
	FragColor = color * lightColor * diffuse + ambient * texColor;

    if ((flags & deformOn) != 0){
        FragColor.r += uTime / 3;
        FragColor.a -= uTime;
    }

}