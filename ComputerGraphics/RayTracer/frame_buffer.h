#pragma once

#include "common.h"
#include "color.h"
#include "mathutil.hpp"
#include "tgaimage.h"

class FrameBuffer
{
public:
	FrameBuffer(int width, int height) : m_Width(width), m_Height(height)
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

	void clear(const Color& clearColor)
	{
		for (int j = 0; j < m_Height; j++)
		{
			for (int i = 0; i < m_Width; i++)
			{
				m_Buffer[j][i] = clearColor;
			}
		}
	}
	void setPixel(int x, int y, const Color& color)
	{
		m_Buffer[y][x] = color;
	}
	void flush() const
	{
		TGAImage image(m_Width, m_Height, TGAImage::RGBA);
		for (int j = 0; j < m_Height; j++)
		{
			for (int i = 0; i < m_Width; i++)
			{
				auto color = m_Buffer[j][i];
				image.set(i, j, TGAColor(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
			}
		}
		image.write_tga_file("ray_tracer.tga");
	}

private:
	int m_Width;
	int m_Height;

	std::vector<std::vector<Color>> m_Buffer;
};