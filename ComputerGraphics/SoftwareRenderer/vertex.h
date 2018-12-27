#pragma once

#include "vec3.hpp"
#include "vec2.hpp"
#include "color.h"

struct Vertex
{
	Vec3f position = Vec3f(0, 0, 0);
	Vec2f uv = Vec2f(0, 0);
	Vec3f normal = Vec3f(0, 1, 0);
	Color color = Color(1, 1, 1, 1);
};
