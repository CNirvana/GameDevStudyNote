#pragma once

#include "tgaimage.h"
#include "vec2.hpp"
#include "vec3.hpp"
#include "model.h"

class Graphics
{
public:
	static void drawLine(Vec2i p0, Vec2i p1, TGAImage& image, const TGAColor& color);
	static void drawTriangle(Vec2i p0, Vec2i p1, Vec2i p2, TGAImage& image, const TGAColor& color);
	static void drawModel(const Model& model, TGAImage& image, const TGAColor& color);
};