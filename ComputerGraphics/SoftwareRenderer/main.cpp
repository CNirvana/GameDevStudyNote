#include <iostream>

#include "tinygl.h"
#include "mathutil.hpp"
#include "mesh.h"
#include "tgaimage.h"

constexpr auto WIDTH = 1024;
constexpr auto HEIGHT = 768;

int main()
{
	TinyGL tinyGL;
	tinyGL.initialize(WIDTH, HEIGHT);

	auto projectionMatrix = Mat4x4::perspective(MathUtil::radius(45.0f), (float)WIDTH / HEIGHT, 1.0f, 100.0f);
	auto viewMatrix = Mat4x4::lookAt({ 0, 10, 16 }, { 0, 0, 0 }, { 0, 1, 0 });

	tinyGL.setViewProjectionMatrix(viewMatrix, projectionMatrix);
	tinyGL.setClearColor(Color::black);
	tinyGL.clear(ClearFlags::ColorBuffer | ClearFlags::DepthBuffer);

	Mesh cube;
	cube.vertices = {
		{{-1, -1, 1}, {}, {}, {1, 0, 0, 1}},
		{{1, -1, 1}, {}, {}, {0, 1, 0, 1}},
		{{1, 1, 1}, {}, {}, {0, 0, 1, 1}},
		{{-1, 1, 1}, {}, {}, {1, 1, 0, 1}},
		{{-1, -1, -1}, {}, {}, {1, 0, 1, 1}},
		{{1, -1, -1}, {}, {}, {0, 1, 1, 1}},
		{{1, 1, -1}, {}, {}, {1, 1, 1, 1}},
		{{-1, 1, -1}, {}, {}, {0, 0, 0, 1}}
	};
	cube.indices = { 0, 1, 2, 0, 2, 3, 1, 5, 6, 1, 6, 2, 5, 4, 7, 5, 7, 5, 4, 0, 3, 4, 3, 7, 0, 4, 5, 0, 5, 1, 3, 2, 6, 3, 6, 7 };

	Mesh triangle;
	triangle.vertices = { {{-1, -1, 0}, {}, {}, {1, 0, 0, 1}}, {{1, -1, 0}, {}, {}, {0, 1, 0, 1}}, {{0, 1, 0}, {}, {}, {0, 0, 1, 1} } };
	triangle.indices = { 0, 1, 2 };

	tinyGL.drawElements(cube.vertices, cube.indices, Mat4x4::scale(5.0f));

	auto colorBuffer = tinyGL.getFrameBuffer()->getColorBuffer();
	auto width = tinyGL.getFrameBuffer()->getWidth();
	auto height = tinyGL.getFrameBuffer()->getHeight();

	TGAImage image(width, height, TGAImage::RGBA);
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			auto color = colorBuffer[i + j * width];
			image.set(i, j, TGAColor(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
		}
	}

	image.write_tga_file("test.tga");

	return 0;
}