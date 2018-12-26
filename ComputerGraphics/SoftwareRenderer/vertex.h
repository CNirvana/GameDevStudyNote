#pragma once

#include "vec3.hpp"
#include "vec2.hpp"
#include "color.h"

struct Vertex
{
	Vec3f position;
	Vec2f uv;
	Vec3f normal;
	Color color;
};
