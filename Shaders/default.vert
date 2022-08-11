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

uniform mat4 meshTransform;
uniform mat4 camPos;
uniform mat4 rotation;
uniform mat4 fRotation;

vec4 check_bones(vec4 model){
    if (aWeights[0] == 0.0)
        return model;
	vec4 position = model;
	position = BoneMatrices[aBones[0]] * aWeights[0] * model;
	position += BoneMatrices[aBones[1]] * aWeights[1] * model;
	position += BoneMatrices[aBones[2]] * aWeights[2] * model;
	return position;
    // return mat4(1.0f);

// //     // vec4 position = model;
// //     // vec4 temp;
// // 	// temp = BoneMatrices[aBones[0]] * model;
// //     // position += temp * aWeights[0];

// // 	// temp =  BoneMatrices[aBones[1]] * model;
// //     // position += temp * aWeights[1];

// // 	// temp = BoneMatrices[aBones[2]] * model;
// //     // position += temp * aWeights[2];
// // 	// return position;
// //     // mat4 transformation = BoneMatrices[aBones[0]] * aWeights[0];
// //     // transformation += BoneMatrices[aBones[1]] * aWeights[1];
// //     // transformation += BoneMatrices[aBones[2]] * aWeights[2];
// //     // if (transformation == mat4(0.0f))
// //     //     transformation = mat4(1.0f);
// //     // return transformation * meshTransform * model;
}

void main()
{
	vec4 model = vec4(aModel, 1.0) * meshTransform;
    // vec4 model = vec4(aModel, 1.0);
    model = check_bones(model);

	// model = fRotation * model * rotation;
	// model.xyz += pos.xyz + fOffset.xyz;


    gl_Position = camPos * model;
	// gl_Position = camPos * vec4(model);
	// gl_Position.xyz += fOffset.xyz;
	_pos = vec3(model.xyz);
	_normal = aNorm;
	_color = aColor;
	_camPos = camPos;
}