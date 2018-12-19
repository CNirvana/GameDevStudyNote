#version 450 core

layout (location = 0) in vec3 n_Pos;
layout (location = 1) in vec3 n_Normal;
layout (location = 2) in vec2 n_TexCoord;

out VS_OUT
{
	vec3 worldPos;
	vec3 normal;
	vec2 texCoord;
} vs_out;

uniform mat4 worldToObj;
uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(n_Pos, 1.0);
	vs_out.texCoord = n_TexCoord;
	vs_out.normal = mat3(worldToObj) * n_Normal;
}