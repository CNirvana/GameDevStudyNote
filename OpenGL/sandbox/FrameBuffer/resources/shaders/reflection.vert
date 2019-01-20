#version 450 core

layout (location = 0) in vec3 n_Position;
layout (location = 1) in vec3 n_Normal;
layout (location = 2) in vec2 n_TexCoord;

out vec2 v_texCoord;
out vec3 v_position;
out vec3 v_normal;

uniform mat4 u_mvp;
uniform mat4 u_world2obj;
uniform mat4 u_model;

void main()
{
    v_normal = mat3(u_world2obj) * n_Normal;
	v_position = vec3(u_model * vec4(n_Position, 1.0));
	gl_Position = u_mvp * vec4(n_Position, 1.0);
	v_texCoord = n_TexCoord;
}