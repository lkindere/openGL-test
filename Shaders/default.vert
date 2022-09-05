#version 330 core

//Model base
layout (location = 0) in vec3 aModel;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aTextures;
layout (location = 4) in ivec3 aBones;
layout (location = 5) in vec3 aWeights;

//instance
layout (location = 6) in vec3 iPos;
layout (location = 7) in vec3 iR1;
layout (location = 8) in vec3 iR2;
layout (location = 9) in vec3 iR3;
layout (location = 10) in float iTime;
layout (location = 11) in int iFlags;

layout (location = 12) in vec4 iBM1;
layout (location = 13) in vec4 iBM2;
layout (location = 14) in vec4 iBM3;
layout (location = 15) in vec4 iBM4;

//instanceFlags
const int deformOn = 1;

// modelFlags
// const int hasTextures = 1;
const int hasBones = 2;

const int MAX_BONES = 30;
const int MAX_iANCES = 1000;

uniform int modelFlags;
uniform mat4 camPos;
uniform samplerBuffer boneTransforms;

out data
{
    vec3 pos;
    vec3 normal;
    vec4 color;
    vec2 texCoords;
    float iTime;
    flat int iFlags;
} data_out;

mat4 fetch_matrix(int boneID){
    return mat4(
    texelFetch(boneTransforms, gl_InstanceID * MAX_BONES * 4 + boneID * 4 + 0), 
    texelFetch(boneTransforms, gl_InstanceID * MAX_BONES * 4 + boneID * 4 + 1),
    texelFetch(boneTransforms, gl_InstanceID * MAX_BONES * 4 + boneID * 4 + 2),
    texelFetch(boneTransforms, gl_InstanceID * MAX_BONES * 4 + boneID * 4 + 3)
    );
}

mat4 check_bones(){
    mat4 bone1 = fetch_matrix(aBones[0]);
    mat4 bone2 = fetch_matrix(aBones[1]);
    mat4 bone3 = fetch_matrix(aBones[2]);

    mat4 boneTransform = bone1 * aWeights[0];
    boneTransform += bone2 * aWeights[1];
    boneTransform += bone3 * aWeights[2];
    return boneTransform;
}

void main()
{
    mat4 rotation = mat4(vec4(iR1, 0.0), vec4(iR2, 0.0), vec4(iR3, 0.0), vec4(0.0, 0.0, 0.0, 1.0));
    vec4 model = vec4(aModel, 1.0);
    vec4 normal = vec4(aNorm, 0.0);

    if ((modelFlags & hasBones) != 0){
        mat4 boneTransform = check_bones();
        model = boneTransform * model;
        normal = boneTransform * normal;
    }

    model = rotation * model;
    model.xyz += iPos.xyz;

    gl_Position = camPos * model;

	data_out.pos = vec3(model.xyz);
	data_out.normal = normal.xyz;
	data_out.color = aColor;
    data_out.texCoords = aTextures;
    data_out.iTime = iTime;
    data_out.iFlags = iFlags;
}