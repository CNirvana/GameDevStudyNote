#version 450 core

in vec2 v_texCoord;

uniform sampler2D u_screenTex;

void main()
{
	FragColor = texture(u_screenTex, v_texCoord);
    float avg = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    gl_FragColor = vec4(avg, avg, avg, 1);
}