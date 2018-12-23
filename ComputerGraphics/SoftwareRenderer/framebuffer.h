#pragma once

#include "tgaimage.h"

class FrameBuffer
{
public:
	FrameBuffer(int width, int height, int format)
	{
		m_ColorBuffer = new TGAImage(width, height, format);
		m_DepthBuffer = new float[width * height];
	}

	virtual ~FrameBuffer()
	{
		if (m_ColorBuffer != nullptr) delete m_ColorBuffer;
		if (m_DepthBuffer != nullptr) delete[] m_DepthBuffer;
	}

	int getWidth() const { return m_ColorBuffer->get_width(); }
	int getHeight() const { return m_ColorBuffer->get_height(); }
	
	void drawPixel(int x, int y, const TGAColor& color)
	{
		m_ColorBuffer->set(x, y, color);
	}

	float getDepth(int x, int y) const
	{
		return m_DepthBuffer[x + y * getWidth()];
	}
	void setDepth(int x, int y, float depth)
	{
		m_DepthBuffer[x + y * getWidth()] = depth;
	}

	void writeToFile(const std::string& filePath, bool flip)
	{
		if (flip)
		{
			m_ColorBuffer->flip_vertically();
		}
		m_ColorBuffer->write_tga_file("image.tga");
	}

	void clear()
	{
		clearDepthBuffer();
	}

protected:
	void clearDepthBuffer()
	{
		for (int i = 0; i < getWidth() * getHeight(); i++) m_DepthBuffer[i] = -std::numeric_limits<float>::max();
	}

private:
	TGAImage* m_ColorBuffer;
	float* m_DepthBuffer;
};