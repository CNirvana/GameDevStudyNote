#version 450 core

layout (location = 0) in vec3 n_Pos;
layout (location = 2) in vec2 n_TexCoord;
layout (location = 3) in mat4 instanceMatrix;

out vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * instanceMatrix * vec4(n_Pos, 1.0);
	texCoord = n_TexCoord;
}