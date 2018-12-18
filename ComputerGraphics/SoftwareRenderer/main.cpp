#include <iostream>

#include "graphics.h"

constexpr auto WIDTH = 512;
constexpr auto HEIGHT = 512;

void drawModel(const Model& model, TGAImage& image, const TGAColor& color)
{
	for (int i = 0; i < model.faces.size(); i++) {
		std::vector<int> face = model.faces[i];
		for (int j = 0; j < 3; j++)
		{
			Vec3f v0 = model.vertices[face[j]];
			Vec3f v1 = model.vertices[face[(j + 1) % 3]];
			int x0 = (v0.x + 1.0) * WIDTH / 2.;
			int y0 = (v0.y + 1.0) * HEIGHT / 2.;
			int x1 = (v1.x + 1.0) * WIDTH / 2.;
			int y1 = (v1.y + 1.0) * HEIGHT / 2.;
			Graphics::drawLine({ x0, y0 }, { x1, y1 }, image, color);
		}
	}
}

void drawModelWithRandomColor(const Model& model, TGAImage& image)
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
		Graphics::drawTriangle(screenCoords[0], screenCoords[1], screenCoords[2], image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
	}
}

void drawModelWithLighting(const Model& model, TGAImage& image)
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
			Graphics::drawTriangle(screenCoords[0], screenCoords[1], screenCoords[2], image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
		}
	}
}

int main()
{
	TGAColor white(255, 255, 255, 255);
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	Model model("./resources/head.obj");
	// drawModelWithRandomColor(model, image);
	drawModelWithLighting(model, image);

	// Graphics::drawTriangle({ 10, 10 }, { 300, 100 }, { 200, 400 }, image, white);

	image.flip_vertically();
	image.write_tga_file("image.tga");

	return 0;
}