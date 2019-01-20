#version 450 core

in vec2 v_texCoord;

uniform sampler2D u_screenTex;

void main()
{
	gl_FragColor = texture(u_screenTex, v_texCoord);
}