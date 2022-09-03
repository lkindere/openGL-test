#version 330 core

layout (location = 0) in vec3 aModel;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aTextures;
layout (location = 4) in ivec3 aBones;
layout (location = 5) in vec3 aWeights;

layout (location = 6) in vec3 instancePos;
layout (location = 7) in mat4 instanceRot;

//Flags
// const int hasTexture = 1;
const int deformOn = 2;

const int MAX_BONES = 30;
uniform mat4 BoneMatrices[MAX_BONES];

uniform float uTime;
uniform int flags;
uniform vec3 pos;
uniform vec3 scale;
uniform mat4 camPos;
uniform mat4 rotation;

out data
{
    vec3 pos;
    vec3 normal;
    vec4 color;
    vec2 texCoords;
} data_out;

mat4 check_bones(){
    if (aWeights[0] == 0.0f)
        return mat4(1.0f);
    mat4 boneTransform = BoneMatrices[aBones[0]] * aWeights[0];
    boneTransform += BoneMatrices[aBones[1]] * aWeights[1];
    boneTransform += BoneMatrices[aBones[2]] * aWeights[2];
    return boneTransform;
}

void main()
{
    vec4 normal = check_bones() * vec4(aNorm, 0.0);
	vec4 model = check_bones() * vec4(aModel, 1.0);


	model = rotation * model * vec4(scale, 1.0f);
	model.xyz += pos.xyz;

    gl_Position = camPos * model;

	data_out.pos = vec3(model.xyz);
	data_out.normal = normal.xyz;
	data_out.color = aColor;
    data_out.texCoords = aTextures;
}