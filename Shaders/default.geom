#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

//instanceFlags
const int deformOn = 1;

// modelFlags
// const int hasTextures = 1;
const int hasBones = 2;

uniform int modelFlags;
uniform mat4 camPos;

in data
{
    vec3 pos;
    vec3 normal;
    vec4 color;
    vec2 texCoords;
    float iTime;
    flat int iFlags;
} data_in[];

out data
{
    vec3 pos;
    vec3 normal;
    vec4 color;
    vec2 texCoords;
    float iTime;
    flat int iFlags;
} data_out;

void main()
{
    vec4 surfaceNormal = vec4(0.0);
    if ((data_in[0].iFlags & deformOn) != 0){
        vec3 v1 = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position);
        vec3 v2 = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
        surfaceNormal = vec4(normalize(cross(v1, v2)), 0.0f);
    }
    gl_Position = gl_in[0].gl_Position + (surfaceNormal * data_in[0].iTime);
    data_out.pos = data_in[0].pos;
    data_out.normal = data_in[0].normal;
    data_out.color = data_in[0].color;
    data_out.texCoords = data_in[0].texCoords;
    data_out.iTime = data_in[0].iTime;
    data_out.iFlags = data_in[0].iFlags;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + (surfaceNormal * data_in[0].iTime);
    data_out.pos = data_in[1].pos;
    data_out.normal = data_in[1].normal;
    data_out.color = data_in[1].color;
    data_out.texCoords = data_in[1].texCoords;
    data_out.iTime = data_in[1].iTime;
    data_out.iFlags = data_in[1].iFlags;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position + (surfaceNormal * data_in[0].iTime);
    data_out.pos = data_in[2].pos;
    data_out.normal = data_in[2].normal;
    data_out.color = data_in[2].color;
    data_out.texCoords = data_in[2].texCoords;
    data_out.iTime = data_in[2].iTime;
    data_out.iFlags = data_in[2].iFlags;
    EmitVertex();

    EndPrimitive();
}