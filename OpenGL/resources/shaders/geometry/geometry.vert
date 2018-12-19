#version 450 core

layout (location = 0) in vec2 n_Pos;
layout (location = 1) in vec3 n_Color;

out VS_OUT
{
    vec3 color;
} vs_out;

void main()
{
    vs_out.color = n_Color;
    gl_Position = vec4(n_Pos.x, n_Pos.y, 0.0, 1.0);
}