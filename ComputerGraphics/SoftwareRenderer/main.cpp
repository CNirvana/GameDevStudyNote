#include <iostream>

#include "graphics.h"
#include "tinygl.h"

constexpr auto WIDTH = 256;
constexpr auto HEIGHT = 256;

void drawModel(const Model& model, FrameBuffer& frameBuffer, const TGAColor& color)
{
	for (int i = 0; i < model.faces.size(); i++) {
		std::vector<int> face = model.faces[i];
		for (int j = 0; j < 3; j++)
		{
			Vec3f v0 = model.vertices[face[j]];
			Vec3f v1 = model.vertices[face[(j + 1) % 3]];
			int x0 = (v0.x + 1.0) * WIDTH * 0.5;
			int y0 = (v0.y + 1.0) * HEIGHT * 0.5;
			int x1 = (v1.x + 1.0) * WIDTH * 0.5;
			int y1 = (v1.y + 1.0) * HEIGHT * 0.5;
			Graphics::drawLine({ x0, y0 }, { x1, y1 }, frameBuffer, color);
		}
	}
}

void drawModelWithRandomColor(const Model& model, FrameBuffer& frameBuffer)
{
	for (int i = 0; i < model.faces.size(); i++)
	{
		std::vector<int> face = model.faces[i];
		Vec2i screenCoords[3];
		for (int j = 0; j < 3; j++)
		{
			Vec3f worldCoords = model.vertices[face[j]];
			screenCoords[j] = Vec2i((worldCoords.x + 1.0) * WIDTH * 0.5, (worldCoords.y + 1.0) * HEIGHT * 0.5);
		}
		Graphics::drawTriangle(screenCoords[0], screenCoords[1], screenCoords[2], frameBuffer, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
	}
}

void drawModelWithLighting(const Model& model, FrameBuffer& frameBuffer)
{
	for (int i = 0; i < model.faces.size(); i++)
	{
		std::vector<int> face = model.faces[i];
		Vec2i screenCoords[3];
		Vec3f worldCoords[3];
		for (int j = 0; j < 3; j++)
		{
			Vec3f v = model.vertices[face[j]];
			screenCoords[j] = Vec2i((v.x + 1.0) * WIDTH * 0.5, (v.y + 1.0) * HEIGHT * 0.5);
			worldCoords[j] = v;
		}
		Vec3f n = (worldCoords[2] - worldCoords[0]).cross(worldCoords[1] - worldCoords[0]);
		Vec3f::normalize(n);
		float intensity = n * Vec3f(0, 0, -1);
		if (intensity > 0)
		{
			Graphics::drawTriangle(screenCoords[0], screenCoords[1], screenCoords[2], frameBuffer, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
		}
	}
}

int main()
{
	TGAColor white(255, 255, 255, 255);
	FrameBuffer frameBuffer(WIDTH, HEIGHT, TGAImage::RGB);
	frameBuffer.clear();

	// Model model("./resources/head.obj");
	// drawModelWithRandomColor(model, image);
	// drawModelWithLighting(model, frameBuffer);
	// Graphics::rasterize({ 10, 10, 0 }, { 200, 100, 0 }, { 100, 200, 0 }, frameBuffer, white);

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