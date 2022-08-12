#version 330 core

layout (location = 0) in vec3 aModel;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec4 aColor;
layout (location = 3) in ivec3 aBones;
layout (location = 4) in vec3 aWeights;

const int MAX_BONES = 20;
uniform mat4 BoneMatrices[MAX_BONES];

out mat4 _camPos;
out vec3 _pos;
out vec3 _normal;
out vec4 _color;

uniform vec3 pos;
uniform vec3 scale;
uniform vec3 fOffset;

uniform mat4 camPos;
uniform mat4 rotation;
uniform mat4 fRotation;

mat4 check_bones(){
    mat4 boneTransform = BoneMatrices[aBones[0]] * aWeights[0];
    boneTransform += BoneMatrices[aBones[1]] * aWeights[1];
    boneTransform += BoneMatrices[aBones[2]] * aWeights[2];
    return boneTransform;
}

void main()
{
	vec4 model = check_bones() * vec4(aModel * scale, 1.0);
    // vec4 model = vec4(aModel, 1.0);

	model = fRotation * model * rotation;
	model.xyz += pos.xyz + fOffset.xyz;


    gl_Position = camPos * model;
	// gl_Position = camPos * vec4(model);
	// gl_Position.xyz += fOffset.xyz;
	_pos = vec3(model.xyz);
	_normal = aNorm;
	_color = aColor;
	_camPos = camPos;
}