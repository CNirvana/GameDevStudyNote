#version 450 core

layout (location = 0) in vec3 n_Pos;
layout (location = 1) in vec3 n_Normal;

out VS_OUT
{
    vec3 normal;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    mat3 normalMat = mat3(transpose(inverse(view * model)));
    vs_out.normal = vec3(projection * vec4(normalMat * n_Normal, 0.0));
    gl_Position = projection * view * model * vec4(n_Pos, 1.0);
}