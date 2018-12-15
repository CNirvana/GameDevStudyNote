#define _CRT_SECURE_NO_WARNINGS

#include "frame_buffer.h"
#include "utility.h"
#include <cstdio>

FrameBuffer::FrameBuffer(int width, int height) : m_Width(width), m_Height(height)
{
	for (int j = 0; j < m_Height; j++)
	{
		m_Buffer.push_back(std::vector<Color>());
		for (int i = 0; i < m_Width; i++)
		{
			m_Buffer[j].push_back(Color::clear);
		}
	}
}

void FrameBuffer::clear(const Color& clearColor)
{
	for (int j = 0; j < m_Height; j++)
	{
		for (int i = 0; i < m_Width; i++)
		{
			m_Buffer[j][i] = clearColor;
		}
	}
}

void FrameBuffer::setPixel(int x, int y, const Color& color)
{
	m_Buffer[y][x] = color;
}

void FrameBuffer::flush() const
{
	FILE* file = std::fopen("test.ppm", "w");
	if (file == nullptr)
	{
		return;
	}

	std::fprintf(file, "P3\n%d %d\n255\n", m_Width, m_Height);
	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			Color c = m_Buffer[y][x];
			std::fprintf(file, "%d %d %d\n", (int)(clamp01(c.r) * 255.99), (int)(clamp01(c.g) * 255.99), (int)(clamp01(c.b) * 255.99));
		}
	}

	std::fclose(file);
}