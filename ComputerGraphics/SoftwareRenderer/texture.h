#pragma once

#include "color.h"
#include "mathutil.hpp"

enum TextureWrapMode
{
	Clamp,
	Repeat
};

class Texture
{
public:
	Texture() : m_Pixels(nullptr), m_Width(0), m_Height(0) {}
	Texture(int width, int height) : m_Width(width), m_Height(height)
	{
		m_Pixels = new Color[width * height];
		clear(Color::clear);
	}
	Texture(Color* pixels, int width, int height) : m_Width(width), m_Height(height)
	{
		m_Pixels = pixels;
	}
	~Texture()
	{
		if (m_Pixels != nullptr)
			delete[] m_Pixels;
	}

	Color getPixel(int x, int y) const
	{
		return m_Pixels[x + y * m_Width];
	}
	void setPixel(int x, int y, const Color& color)
	{
		m_Pixels[x + y * m_Width] = color;
	}

	const Color* getPixels() const { return m_Pixels; }
	void setPixels(Color* pixels, int width, int height)
	{
		m_Pixels = pixels;
		m_Width = width;
		m_Height = height;
	}

	void clear(const Color& clearColor)
	{
		for (int i = 0; i < m_Width * m_Height; i++)
			m_Pixels[i] = clearColor;
	}

	Color sample(const Vec2f& texCoord) const
	{
		float u = texCoord.x;
		float v = texCoord.y;
		switch (m_WrapMode)
		{
		case TextureWrapMode::Clamp:
			{
				u = MathUtil::clamp(u, 0, 1);
				v = MathUtil::clamp(v, 0, 1);
			}
			break;
		case TextureWrapMode::Repeat:
			{
				u = u - std::floorf(u);
				v = v - std::floorf(v);
			}
			break;
		default:
			break;
		}

		v = 1 - v;

		return getPixel(u * (m_Width - 1), v * (m_Height - 1));
	}

	int getWidth() const { return m_Width; }
	int getHeight() const { return m_Height; }
	TextureWrapMode getTextureWrapMode() const { return m_WrapMode; }
	void setTextureWrapMode(TextureWrapMode wrapMode) { m_WrapMode = wrapMode; }

private:
	Color* m_Pixels;
	int m_Width;
	int m_Height;

	TextureWrapMode m_WrapMode;
};