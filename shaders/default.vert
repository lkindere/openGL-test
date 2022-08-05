#version 330 core

layout (location = 0) in vec3 aModel;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec4 aColor;
layout (location = 3) in ivec3 aBones;
layout (location = 4) in vec3 aWeights;

// const int MAX_WEIGHTS = 3;
// const int MAX_BONES = 20;
// uniform mat4 BoneMatrices[MAX_BONES];

out mat4 _camPos;
out vec3 _pos;
out vec3 _normal;
out vec4 _color;

uniform mat4 camPos;
uniform vec3 pos;
uniform vec3 scale;
uniform mat4 rotation;

uniform vec3 fOffset;
uniform mat4 fRotation;

// vec4 check_bones(vec4 model){
// 	vec4 position = vec4(0.0f);
// 	for (int i = 0; i < MAX_WEIGHTS; ++i){
// 		if (aBones[i] == -1)
// 			break ;
// 		vec4 localPosition = BoneMatrices[aBones[i]] * model;
// 		position += localPosition * aWeights[i];
// 		//Normals ??? 
// 	}
// 	return position;
// }

void main()
{
	vec4 model = fRotation * vec4(aModel * scale, 1.0) * rotation;
	model.xyz += pos.xyz;

	// check_bones(model);

	gl_Position = camPos * vec4(model);
	gl_Position.xyz += fOffset.xyz;
	_pos = vec3(pos + model.xyz);
	_normal = aNorm;
	_color = aColor;
	_camPos = camPos;
}