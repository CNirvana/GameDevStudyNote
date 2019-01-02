#include <iostream>

#include "tinygl.h"
#include "mathutil.hpp"
#include "mesh.h"
#include "tgaimage.h"

constexpr auto WIDTH = 1024;
constexpr auto HEIGHT = 768;

Texture* loadTexture(const std::string& path)
{
	TGAImage img;
	img.read_tga_file(path.c_str());
	int width = img.get_width();
	int height = img.get_height();

	Color* pixels = new Color[width * height];
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			TGAColor c = img.get(i, j);
			pixels[i + j * width] = Color(c.bgra[2] / 255.0f, c.bgra[1] / 255.0f, c.bgra[0] / 255.0f, 1);
		}
	}

	return new Texture(pixels, width, height);
}

void saveImage(const Color* pixels, int width, int height, std::string fileName)
{
	TGAImage image(width, height, TGAImage::RGBA);
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			auto color = pixels[i + j * width];
			image.set(i, j, TGAColor(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
		}
	}
	image.write_tga_file(fileName.c_str());
}

int main()
{
	Texture* texture1 = loadTexture("resources/test.tga");

	TinyGL tinyGL;
	tinyGL.initialize(WIDTH, HEIGHT);

	auto projectionMatrix = Mat4x4::perspective(MathUtil::radius(45.0f), (float)WIDTH / HEIGHT, 1.0f, 100.0f);
	auto viewMatrix = Mat4x4::lookAt({ 0, 10, 16 }, { 0, 0, 0 }, { 0, 1, 0 });

	tinyGL.setViewProjectionMatrix(viewMatrix, projectionMatrix);
	tinyGL.setClearColor(Color::black);
	tinyGL.clear(ClearFlags::ColorBuffer | ClearFlags::DepthBuffer);

	Mesh quad;
	quad.vertices = {
		{{-1, -1, 0}, {0, 0}, {0, 0, 1}, {0, 0, 0, 1}},
		{{1, -1, 0}, {1, 0}, {0, 0, 1}, {1, 1, 1, 1}},
		{{-1, 1, 0}, {0, 1}, {0, 0, 1}, {0, 0, 0, 1}},
		{{1, 1, 0}, {1, 1}, {0, 0, 1}, {1, 1, 1, 1}}
	};
	quad.indices = { 0, 1, 2, 1, 3, 2 };

	Mesh triangle;
	triangle.vertices = { {{-1, -1, 0}, {}, {}, {1, 0, 0, 1}}, {{1, -1, 0}, {}, {}, {0, 1, 0, 1}}, {{0, 1, 0}, {}, {}, {0, 0, 1, 1} } };
	triangle.indices = { 0, 1, 2 };

	tinyGL.bindTexture(texture1, 0);
	tinyGL.drawElements(quad.vertices, quad.indices, Mat4x4::scale(5.0f));

	auto colorBuffer = tinyGL.getFrameBuffer()->getColorBuffer();
	auto depthBuffer = tinyGL.getFrameBuffer()->getDepthBuffer();
	auto width = tinyGL.getFrameBuffer()->getWidth();
	auto height = tinyGL.getFrameBuffer()->getHeight();

	saveImage(colorBuffer->getPixels(), width, height, "color_buffer.tga");

	delete texture1;

	return 0;
}