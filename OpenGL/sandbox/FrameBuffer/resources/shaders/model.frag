#version 450 core

in vec2 v_texCoord;

uniform sampler2D u_texture_diffuse1;

void main()
{
	gl_FragColor = vec4(texture(u_texture_diffuse1, v_texCoord).rgb, 1);
}