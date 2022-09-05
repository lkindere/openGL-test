#version 330 core

//instanceFlags
const int deformOn = 1;

// modelFlags
const int hasTextures = 1;
// const int hasBones = 2;

const vec4 ambient = vec4(0.15f, 0.15f, 0.15f, 1.0f);

uniform int modelFlags;
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
    float iTime;
    flat int iFlags;
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

    if ((modelFlags & hasTextures) != 0)
        texColor = texture(image, data_in.texCoords);
    
	FragColor = color * lightColor * diffuse + ambient * texColor;

    if ((data_in.iFlags & deformOn) != 0){
        FragColor.r += data_in.iTime / 3;
        FragColor.a -= data_in.iTime;
    }

}