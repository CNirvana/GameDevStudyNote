#version 450 core

layout (location = 0) in vec3 n_Position;
layout (location = 1) in vec3 n_Normal;
layout (location = 2) in vec2 n_TexCoord;

out VS_OUT
{
	vec3 normal;
	vec2 texCoord;
	vec3 worldPos;
} vs_out;

uniform mat4 u_worldToObj;
uniform mat4 u_mvp;
uniform mat4 u_model;

void main()
{
	gl_Position = u_mvp * vec4(n_Position, 1.0);
	vs_out.texCoord = n_TexCoord;
	vs_out.normal = mat3(u_worldToObj) * n_Normal;
	vs_out.worldPos = (u_model * vec4(n_Position, 1.0)).xyz;
}