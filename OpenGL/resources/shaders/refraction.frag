#version 450 core

in vec2 v_texCoord;
in vec3 v_position;
in vec3 v_normal;

uniform vec3 u_camera_pos;
uniform samplerCube u_skybox;

void main()
{
    float ratio = 1.0 / 1.52;
	vec3 viewDir = normalize(u_camera_pos - v_position);
	vec3 refr = refract(-viewDir, normalize(v_normal), ratio);
	gl_FragColor = vec4(texture(u_skybox, refr).rgb, 1);
}