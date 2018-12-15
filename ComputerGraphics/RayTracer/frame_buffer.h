#pragma once

#include "color.h"
#include <vector>

class FrameBuffer
{
public:
	FrameBuffer(int width, int height);

	void clear(const Color& clearColor);
	void setPixel(int x, int y, const Color& color);
	void flush() const;

private:
	int m_Width;
	int m_Height;

	std::vector<std::vector<Color>> m_Buffer;
};