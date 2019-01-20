#version 450 core

in vec2 v_texCoord;
in vec3 v_position;
in vec3 v_normal;

uniform vec3 u_camera_pos;
uniform samplerCube u_skybox;

void main()
{
	vec3 viewDir = normalize(u_camera_pos - v_position);
	vec3 refl = reflect(-viewDir, normalize(v_normal));
	gl_FragColor = vec4(texture(u_skybox, refl).rgb, 1);
}