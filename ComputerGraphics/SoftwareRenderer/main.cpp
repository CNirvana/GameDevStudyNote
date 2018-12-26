#include <iostream>

#include "tinygl.h"
#include "mathutil.hpp"
#include "tgaimage.h"

constexpr auto WIDTH = 256;
constexpr auto HEIGHT = 256;

int main()
{
	TinyGL tinyGL;
	tinyGL.initialize(WIDTH, HEIGHT);

	auto projectionMatrix = Mat4x4::perspective(MathUtil::radius(90.0f), (float)WIDTH / HEIGHT, 1.0f, 100.0f);
	auto viewMatrix = Mat4x4::lookAt({ 0, 5, 16 }, { 0, 0, 0 }, { 0, 1, 0 });

	tinyGL.setViewProjectionMatrix(viewMatrix, projectionMatrix);
	tinyGL.clear(ClearFlags::ColorBuffer | ClearFlags::DepthBuffer);

	tinyGL.drawElements({
			{{-5, -5, 0}, {0, 0}, {0, 0, 1}, {1, 0, 0, 0}},
			{{-5, 5, 0}, {0, 0}, {0, 0, 1}, {1, 0, 0, 0}},
			{{0, 5, 0}, {0, 0}, {0, 0, 1}, {1, 0, 0, 0}}
		}, { 0, 1, 2 }, Mat4x4(1.0f));

	auto colorBuffer = tinyGL.getFrameBuffer()->getColorBuffer();
	auto width = tinyGL.getFrameBuffer()->getWidth();
	auto height = tinyGL.getFrameBuffer()->getHeight();

	TGAImage image;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			auto color = colorBuffer[i + j * width];
			image.set(i, j, TGAColor(color.r, color.g, color.b, color.a));
		}
	}

	image.write_tga_file("test.tga");

	return 0;
}