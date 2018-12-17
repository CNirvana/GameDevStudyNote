#include <iostream>

#include "graphics.h"

constexpr auto WIDTH = 512;
constexpr auto HEIGHT = 512;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = std::abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {
		if (steep) {
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}
		error2 += derror2;
		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

int main()
{
	TGAColor white(255, 255, 255, 255);
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	// Model model("./resources/head.obj");
	// Graphics::drawModel(model, image, white);

	Graphics::drawTriangle({ 10, 10 }, { 300, 100 }, { 200, 400 }, image, white);

	image.flip_vertically();
	image.write_tga_file("image.tga");

	return 0;
}