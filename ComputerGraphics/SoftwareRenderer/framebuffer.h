#pragma once

#include "texture.h"

class FrameBuffer
{
public:
	FrameBuffer(int width, int height) : m_Width(width), m_Height(height)
	{
		m_ColorBuffer = new Texture(width, height);
		m_DepthBuffer = new float[width * height];
	}

	virtual ~FrameBuffer()
	{
		if (m_ColorBuffer != nullptr) delete m_ColorBuffer;
		if (m_DepthBuffer != nullptr) delete[] m_DepthBuffer;
	}

	void resize(int width, int height)
	{
		if (m_ColorBuffer != nullptr) delete m_ColorBuffer;
		if (m_DepthBuffer != nullptr) delete[] m_DepthBuffer;

		m_Width = width;
		m_Height = height;
		m_ColorBuffer = new Texture(width, height);
		m_DepthBuffer = new float[width * height];
	}

	int getWidth() const { return m_Width; }
	int getHeight() const { return m_Height; }
	
	void setPixel(int x, int y, const Color& color)
	{
		m_ColorBuffer->setPixel(x, y, color);
	}

	float getDepth(int x, int y) const
	{
		return m_DepthBuffer[x + y * getWidth()];
	}
	void setDepth(int x, int y, float depth)
	{
		m_DepthBuffer[x + y * getWidth()] = depth;
	}

	void clearDepthBuffer()
	{
		for (int i = 0; i < getWidth() * getHeight(); i++)
			m_DepthBuffer[i] = std::numeric_limits<float>::max();
	}

	void clearColorBuffer(const Color& clearColor)
	{
		m_ColorBuffer->clear(clearColor);
	}

	const Texture* getColorBuffer() const { return m_ColorBuffer; }
	const float* getDepthBuffer() const { return m_DepthBuffer; }

private:
	Texture* m_ColorBuffer;
	float* m_DepthBuffer;

	int m_Width;
	int m_Height;
};