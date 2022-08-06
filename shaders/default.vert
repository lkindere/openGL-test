#version 330 core

layout (location = 0) in vec3 aModel;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec4 aColor;
layout (location = 3) in ivec3 aBones;
layout (location = 4) in vec3 aWeights;

const int MAX_WEIGHTS = 3;
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

vec4 check_bones(vec4 model){
	vec4 position = model;
	position += BoneMatrices[aBones[0]] * aWeights[0] * model;
	position += BoneMatrices[aBones[1]] * aWeights[1] * model;
	position += BoneMatrices[aBones[2]] * aWeights[2] * model;
	return position;
    // mat4 transformation = BoneMatrices[aBones[0]] * aWeights[0];
    // transformation += BoneMatrices[aBones[1]] * aWeights[1];
    // transformation += BoneMatrices[aBones[2]] * aWeights[2];
    // return transformation * model;
}

void main()
{
	vec4 model = fRotation * vec4(aModel * scale, 1.0) * rotation;
	model.xyz += pos.xyz;

	model = check_bones(model);

	gl_Position = camPos * vec4(model);
	gl_Position.xyz += fOffset.xyz;
	_pos = vec3(pos + model.xyz);
	_normal = aNorm;
	_color = aColor;
	_camPos = camPos;
}