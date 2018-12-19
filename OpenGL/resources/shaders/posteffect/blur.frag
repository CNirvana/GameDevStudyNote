#version 450 core

in vec2 v_texCoord;

uniform sampler2D u_screenTex;
uniform vec4 u_screenTex_texelSize;

void main()
{
    float xOffset = u_screenTex_texelSize.x;
    float yOffset = u_screenTex_texelSize.y;

    vec2 offset[9] = vec2[]
    (
        vec2(-xOffset, yOffset),
        vec2(0, yOffset),
        vec2(xOffset, yOffset),
        vec2(-xOffset, 0),
        vec2(0, 0),
        vec2(xOffset, 0),
        vec2(-xOffset, -yOffset),
        vec2(0, -yOffset),
        vec2(xOffset, -yOffset)
    );
    float kernel[9] = float[]
    (
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16
    );

    vec3 col = vec3(0);
    for(int i = 0; i < 9; i++)
    {
        col += (vec3(texture(u_screenTex, v_texCoord.st + offset[i])) * kernel[i]);
    }

	gl_FragColor = vec4(col, 1);
}