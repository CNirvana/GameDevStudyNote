#pragma once

#include "color.h"

class FrameBuffer
{
public:
	FrameBuffer(int width, int height) : m_Width(width), m_Height(height)
	{
		m_ColorBuffer = new Color[width * height];
		m_DepthBuffer = new float[width * height];
	}

	virtual ~FrameBuffer()
	{
		if (m_ColorBuffer != nullptr) delete[] m_ColorBuffer;
		if (m_DepthBuffer != nullptr) delete[] m_DepthBuffer;
	}

	void resize(int width, int height)
	{
		if (m_ColorBuffer != nullptr) delete[] m_ColorBuffer;
		if (m_DepthBuffer != nullptr) delete[] m_DepthBuffer;

		m_Width = width;
		m_Height = height;
		m_ColorBuffer = new Color[width * height];
		m_DepthBuffer = new float[width * height];
	}

	int getWidth() const { return m_Width; }
	int getHeight() const { return m_Height; }
	
	void setPixel(int x, int y, const Color& color)
	{
		m_ColorBuffer[x + y * getWidth()] = color;
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
			m_DepthBuffer[i] = 1.0f;
	}

	void clearColorBuffer(const Color& clearColor)
	{
		for (int i = 0; i < getWidth() * getHeight(); i++)
			m_ColorBuffer[i] = clearColor;
	}

	const Color* getColorBuffer() const { return m_ColorBuffer; }
	const float* getDepthBuffer() const { return m_DepthBuffer; }

private:
	Color* m_ColorBuffer;
	float* m_DepthBuffer;

	int m_Width;
	int m_Height;
};