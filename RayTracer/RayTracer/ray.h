#pragma once

#include "vec3.hpp"

class Entity;

struct RaycastResult
{
	Entity* hit;
	float distance;
	Vec3f position;
	Vec3f normal;

	RaycastResult() : hit(nullptr), distance(0), position(0, 0, 0), normal(0, 0, 0) {}
	RaycastResult(Entity* const _hit, float _distance, const Vec3f& _position, const Vec3f& _normal)
		: hit(_hit), distance(_distance), position(_position), normal(_normal) {}
};

struct Ray
{
	Vec3f origin;
	Vec3f direction;

	Ray(const Vec3f& _origin, const Vec3f& _direction)
		: origin(_origin), direction(_direction) {}

	Vec3f getPoint(float distance) const
	{
		return origin + direction * distance;
	}
};