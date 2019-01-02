#pragma once

#include "vec4.hpp"
#include "vertex.h"
#include "renderstates.h"

struct VertIn
{
	Vec3f position;
	Vec2f texCoord;
	Vec3f normal;
	Color color;

	VertIn(const Vertex& vertex) : position(vertex.position), texCoord(vertex.uv), normal(vertex.normal), color(vertex.color)
	{}
};

struct VertOut
{
	Vec4f position;
	Vec3f worldPos;
	Vec2f texCoord;
	Vec3f normal;
	Color color;
};

class IShader
{
public:
	virtual void vert(const VertIn* IN, VertOut* OUT) = 0;
	virtual Color frag(const VertOut* IN) = 0;
};

class DefaultShader : public IShader
{
public:
	void vert(const VertIn* IN, VertOut* OUT) override
	{
		OUT->position = RenderStates::get().getModelViewProjectionMatrix() * Vec4f(IN->position.x, IN->position.y, IN->position.z, 1.0f);
		OUT->worldPos = RenderStates::get().getModelMatrix() * IN->position;
		OUT->texCoord = IN->texCoord;
		OUT->normal = IN->normal;
		OUT->color = IN->color;
	}

	Color frag(const VertOut* IN) override
	{
		const Vec3f lightDir(1.0f, 1.0f, 1.0f);
		float NdotL = std::max(0.0f, Vec3f::dot(Vec3f::normalize(IN->normal), Vec3f::normalize(lightDir)));
		Color col = RenderStates::get().getTexture(0)->sample(IN->texCoord);
		col *= NdotL;
		col.a = 1.0f;
		return col;
	}
};