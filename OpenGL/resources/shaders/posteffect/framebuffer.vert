#version 450 core

layout (location = 0) in vec3 n_Position;
layout (location = 1) in vec2 n_TexCoord;

out vec2 v_texCoord;

void main()
{
	gl_Position = vec4(n_Position.x, n_Position.y, 0, 1.0);
	v_texCoord = n_TexCoord;
}