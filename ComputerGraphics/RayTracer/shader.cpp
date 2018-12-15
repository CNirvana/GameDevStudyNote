#include "shader.h"

Color Shader_Unlit::fragment(const FragInput& input)
{
	return m_Color;
}

Color Shader_Lit::fragment(const FragInput& input)
{
	float NdotL = input.normal.dot(input.lightDir);
	Vec3f half = (input.viewDir + input.lightDir).normalize();
	float NdotH = input.normal.dot(half);

	Color diff = m_Diffuse * std::max(NdotL, 0.0f);
	Color spec = m_Specular * std::pow(std::max(NdotH, 0.0f), m_Shininess);

	Color col = input.lightColor * (diff + spec);
	col.a = 1;
	return col;
}