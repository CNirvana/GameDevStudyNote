#version 450 core

layout (location = 0) in vec3 n_Position;
layout (location = 1) in vec3 n_Normal;
layout (location = 2) in vec2 n_TexCoord;

out vec2 v_texCoord;

uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp * vec4(n_Position, 1.0);
	v_texCoord = n_TexCoord;
}