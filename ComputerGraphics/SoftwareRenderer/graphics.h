#pragma once

#include <algorithm>
#include <limits>

#include "tgaimage.h"
#include "vec2.hpp"
#include "vec3.hpp"
#include "rect.hpp"
#include "model.h"
#include "framebuffer.h"

class Graphics
{
public:
	static void drawLine(Vec2i p0, Vec2i p1, FrameBuffer& frameBuffer, const TGAColor& color);
	static void drawTriangle(Vec2i p0, Vec2i p1, Vec2i p2, FrameBuffer& frameBuffer, const TGAColor& color);
	static void rasterize(Vec3f p0, Vec3f p1, Vec3f p2, FrameBuffer& image, const TGAColor& color);
	static Vec3f barycentric(Vec3f p0, Vec3f p1, Vec3f p2, Vec3f p);
};