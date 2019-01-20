#pragma once

#include "color.h"
#include "vec3.hpp"

struct FragInput
{
	Vec3f position;
	Vec3f normal;
	Vec3f viewDir;
	Vec3f lightDir;
	Color lightColor;
};

class Shader
{
public:
	Shader(const Color& color) : m_Color(color) {}
	virtual Color fragment(const FragInput& input) = 0;

	const Color& getColor() const { return m_Color; }
	void setColor(const Color& color) { m_Color = color; }

protected:
	Color m_Color;

};

class Shader_Unlit : public Shader
{
public:
	Shader_Unlit(const Color& color) : Shader(color) {}

	virtual Color fragment(const FragInput& input) override
	{
		return m_Color;
	}
};

class Shader_Lit : public Shader
{
public:
	Shader_Lit(const Color& color, const Color& diffuse, const Color& specular, float shininess) 
		: Shader(color), m_Diffuse(diffuse), m_Specular(specular), m_Shininess(shininess) {}

	virtual Color fragment(const FragInput& input) override
	{
		float NdotL = input.normal.dot(input.lightDir);
		Vec3f half = Vec3f::normalize(input.viewDir + input.lightDir);
		float NdotH = input.normal.dot(half);

		Color diff = m_Diffuse * std::max(NdotL, 0.0f);
		Color spec = m_Specular * std::pow(std::max(NdotH, 0.0f), m_Shininess);

		Color col = input.lightColor * (diff + spec);
		col.a = 1;
		return col;
	}

private:
	Color m_Diffuse;
	Color m_Specular;
	float m_Shininess;
};