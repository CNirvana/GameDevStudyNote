#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

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

void run()
{
	Mesh mesh("resources/head.obj");
	Texture* texture1 = loadTexture("resources/african_head_diffuse.tga");

	TinyGL tinyGL;
	tinyGL.initialize(WIDTH, HEIGHT);

	auto projectionMatrix = Mat4x4::perspective(MathUtil::radius(45.0f), (float)WIDTH / HEIGHT, 1.0f, 100.0f);
	auto viewMatrix = Mat4x4::lookAt({ 0, 2, 5 }, { 0, 0, 0 }, { 0, 1, 0 });

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
	tinyGL.drawElements(mesh.vertices, mesh.indices, Mat4x4::scale(1.0f));

	auto colorBuffer = tinyGL.getFrameBuffer()->getColorBuffer();
	auto depthBuffer = tinyGL.getFrameBuffer()->getDepthBuffer();
	auto width = tinyGL.getFrameBuffer()->getWidth();
	auto height = tinyGL.getFrameBuffer()->getHeight();

	saveImage(colorBuffer->getPixels(), width, height, "color_buffer.tga");

	delete texture1;
}

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_Texture* gTexture;
Uint32* gBackBuffer;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &gWindow, &gRenderer);
	gTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
	gBackBuffer = new Uint32[WIDTH * HEIGHT];
}

void flush(const Color* pixels)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			Uint32 iColor = ((uint8_t)(255.0f * pixels[i * WIDTH + j].b) << 16) |
				((uint8_t)(255.0f * pixels[i * WIDTH + j].g) << 8) |
				((uint8_t)(255.0f * pixels[i * WIDTH + j].r)) & 0xffffff;

			gBackBuffer[i * WIDTH + j] = iColor;
		}
	}

	SDL_UpdateTexture(gTexture, NULL, gBackBuffer, WIDTH * sizeof(Uint32));
	SDL_RenderClear(gRenderer);
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
	SDL_RenderPresent(gRenderer);
}

int main(int argc, char** argv)
{
	if (!init())
	{
		return 1;
	}

	SDL_Event ev;

	Mesh mesh("resources/head.obj");
	Texture* texture = loadTexture("resources/african_head_diffuse.tga");

	TinyGL tinyGL;
	tinyGL.initialize(WIDTH, HEIGHT);

	int frame = 0;
	float lastTime = SDL_GetTicks() * 0.001f;

	while (true)
	{
		if (SDL_PollEvent(&ev) && ev.type == SDL_QUIT)
		{
			break;
		}

		auto projectionMatrix = Mat4x4::perspective(MathUtil::radius(45.0f), (float)WIDTH / HEIGHT, 1.0f, 100.0f);
		auto viewMatrix = Mat4x4::lookAt({ 0, sin((float)SDL_GetTicks() * 0.001f) * 2, 5 }, { 0, 0, 0 }, { 0, 1, 0 });

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

		tinyGL.bindTexture(texture, 0);
		tinyGL.drawElements(mesh.vertices, mesh.indices, Mat4x4::scale(1.0f));

		auto colorBuffer = tinyGL.getFrameBuffer()->getColorBuffer();

		flush(colorBuffer->getPixels());

		frame++;
		float currentTime = SDL_GetTicks() * 0.001f;
		float dt = currentTime - lastTime;
		lastTime = currentTime;

		if ((frame % 60 ) == 0)
		{
			std::cout << "FPS: " << (int)(1 / dt) << std::endl;
		}
	}

	delete texture;

	SDL_Quit();

	return 0;
}