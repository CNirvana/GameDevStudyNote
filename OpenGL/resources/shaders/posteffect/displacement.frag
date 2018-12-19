#version 450 core

in vec2 v_texCoord;

uniform sampler2D u_screenTex;
uniform vec4 u_screenTex_texelSize;
uniform float u_time;

const float speed = 0.2;;
const float frequency = 9.0;

vec2 shift(vec2 p)
{
	float d = u_time * speed;
	float x = frequency * (p.x + d);
	float y = frequency * (p.y + d);
	return vec2(cos(x - y) * cos(y), sin(x + y) * sin(y));
}

void main()
{
	vec2 st = v_texCoord;
	vec2 p = shift(st);
	vec2 q = shift(st + 1.0);
	float amplitude = 2.0 / u_screenTex_texelSize.z;
	vec2 s = st + amplitude * (p - q);

	gl_FragColor = texture(u_screenTex, s);
}