#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

//Flags
// const int hasTexture = 1;
const int deformOn = 2;

uniform int modelFlags;
uniform mat4 camPos;

in data
{
    vec3 pos;
    vec3 normal;
    vec4 color;
    vec2 texCoords;
} data_in[];

out data
{
    vec3 pos;
    vec3 normal;
    vec4 color;
    vec2 texCoords;
} data_out;

void main()
{
    vec4 surfaceNormal = vec4(0.0);
    // if ((flags & deformOn) != 0){
    //     vec3 v1 = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position);
    //     vec3 v2 = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
    //     surfaceNormal = vec4(normalize(cross(v1, v2)), 0.0f);
    // }
    
        //gl_Position = gl_in[0].gl_Position + (surfaceNormal * uTime);
    gl_Position = gl_in[0].gl_Position + (surfaceNormal);
    data_out.pos = data_in[0].pos;
    data_out.normal = data_in[0].normal;
    data_out.color = data_in[0].color;
    data_out.texCoords = data_in[0].texCoords;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + (surfaceNormal);
    data_out.pos = data_in[1].pos;
    data_out.normal = data_in[1].normal;
    data_out.color = data_in[1].color;
    data_out.texCoords = data_in[1].texCoords;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position + (surfaceNormal);
    data_out.pos = data_in[2].pos;
    data_out.normal = data_in[2].normal;
    data_out.color = data_in[2].color;
    data_out.texCoords = data_in[2].texCoords;
    EmitVertex();

    EndPrimitive();
}