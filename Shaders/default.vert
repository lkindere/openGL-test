#version 330 core

layout (location = 0) in vec3 aModel;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aTextures;
layout (location = 4) in ivec3 aBones;
layout (location = 5) in vec3 aWeights;

const int MAX_BONES = 20;
uniform mat4 BoneMatrices[MAX_BONES];

out mat4 _camPos;
out vec3 _pos;
out vec3 _normal;
out vec4 _color;
out vec2 _texCoords;

uniform vec3 pos;
uniform vec3 scale;
uniform vec3 fOffset;

uniform mat4 camPos;
uniform mat4 rotation;
uniform mat4 fRotation;

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

	model = model * rotation * vec4(scale, 1.0f);
	model.xyz += pos.xyz + fOffset.xyz;

    gl_Position = camPos * model;

	_pos = vec3(model.xyz);
	_normal = aNorm;
	_color = aColor;
    _texCoords = aTextures;
	_camPos = camPos;
}