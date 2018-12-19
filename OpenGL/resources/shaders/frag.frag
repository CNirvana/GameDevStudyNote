#version 450 core

in vec2 v_texCoord;

uniform sampler2D u_mainTex;

void main()
{
	gl_FragColor = texture(u_mainTex, v_texCoord); // discard
}