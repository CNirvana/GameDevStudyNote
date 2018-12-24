#include <iostream>

#include "graphics.h"
#include "tinygl.h"
#include "mat4.hpp"
#include "mathutil.hpp"

constexpr auto WIDTH = 256;
constexpr auto HEIGHT = 256;

int main()
{
	TGAColor white(255, 255, 255, 255);
	FrameBuffer frameBuffer(WIDTH, HEIGHT, TGAImage::RGB);
	frameBuffer.clear();

	Vec2f v0(-0.5, -0.5);
	Vec2f v1(0.5, -0.5);
	Vec2f v2(0, 0.5);
	Vec3f c0(255, 0, 0);
	Vec3f c1(0, 255, 0);
	Vec3f c2(0, 0, 255);

	v0.x = (v0.x + 1) * 0.5 * WIDTH, v0.y = (1 - v0.y) * 0.5 * HEIGHT;
	v1.x = (v1.x + 1) * 0.5 * WIDTH, v1.y = (1 - v1.y) * 0.5 * HEIGHT;
	v2.x = (v2.x + 1) * 0.5 * WIDTH, v2.y = (1 - v2.y) * 0.5 * HEIGHT;

	float area = edgeFunction(v0.x, v0.y, v1.x, v1.y, v2.x, v2.y);
	float invArea = 1.0f / area;
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			Vec3f p(i + 0.5f, j + 0.5f, 0);
			float w0 = edgeFunction(v1.x, v1.y, v2.x, v2.y, p.x, p.y);
			float w1 = edgeFunction(v2.x, v2.y, v0.x, v0.y, p.x, p.y);
			float w2 = edgeFunction(v0.x, v0.y, v1.x, v1.y, p.x, p.y);

			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				w0 *= invArea;
				w1 *= invArea;
				w2 *= invArea;

				float r = w0 * c0.x + w1 * c1.x + w2 * c2.x;
				float g = w0 * c0.y + w1 * c1.y + w2 * c2.y;
				float b = w0 * c0.z + w1 * c1.z + w2 * c2.z;

				frameBuffer.drawPixel(i, j, TGAColor(r, g, b));
			}
		}
	}

	frameBuffer.writeToFile("image.tga", false);

	return 0;
}