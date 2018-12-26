#include "graphics.h"

void Graphics::drawLine(Vec2i p0, Vec2i p1, FrameBuffer& frameBuffer, const TGAColor& color)
{
	bool steep = false;
	if (std::abs(p0.x - p1.x) < std::abs(p0.y - p1.y))
	{
		std::swap(p0.x, p0.y);
		std::swap(p1.x, p1.y);
		steep = true;
	}

	if (p0.x > p1.x)
	{
		std::swap(p0, p1);
	}

	int dx = p1.x - p0.x;
	int dy = p1.y - p0.y;
	float derror = std::abs(dy) * 2;
	float error = 0;
	int y = p0.y;

	for (int x = p0.x; x <= p1.x; x++)
	{
		if (steep)
		{
			// frameBuffer.drawPixel(y, x, color);
		}
		else
		{
			// frameBuffer.drawPixel(x, y, color);
		}

		error += derror;
		if (error > dx)
		{
			y += (p1.y > p0.y ? 1 : -1);
			error -= dx * 2;
		}
	}
}

void Graphics::drawTriangle(Vec2i p0, Vec2i p1, Vec2i p2, FrameBuffer& frameBuffer, const TGAColor& color)
{
	if (p0.y > p1.y)
	{
		std::swap(p0, p1);
	}
	if (p1.y > p2.y)
	{
		std::swap(p1, p2);
	}
	if (p0.y > p1.y)
	{
		std::swap(p0, p1);
	}

	int totalHeight = p2.y - p0.y;
	Vec2i p2mp0 = p2 - p0;
	Vec2i p2mp1 = p2 - p1;
	Vec2i p1mp0 = p1 - p0;
	for (int i = 0; i < totalHeight; i++)
	{
		bool secondHalf = i > p1.y - p0.y || p1.y == p0.y;
		int segmentHeight = secondHalf ? p2.y - p1.y : p1.y - p0.y;
		float alpha = (float)i / totalHeight;
		float beta = (float)(i - (secondHalf ? p1.y - p0.y : 0)) / segmentHeight;
		int A = p0.x + p2mp0.x * alpha;
		int B = secondHalf ? p1.x + p2mp1.x * beta : p0.x + p1mp0.x * beta;
		if (A > B)
		{
			std::swap(A, B);
		}
		for (int j = A; j <= B; j++)
		{
			// frameBuffer.drawPixel(j, p0.y + i, color);
		}
	}
}

void Graphics::rasterize(Vec3f p0, Vec3f p1, Vec3f p2, FrameBuffer& frameBuffer, const TGAColor& color)
{
	Rectf rect(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(),
		std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
	rect.xMin = std::max(0.0f, std::min(rect.xMin, p0.x));
	rect.yMin = std::max(0.0f, std::min(rect.yMin, p0.y));
	rect.xMax = std::min(frameBuffer.getWidth() - 1.0f, std::max(rect.xMax, p0.x));
	rect.yMax = std::min(frameBuffer.getHeight() - 1.0f, std::max(rect.yMax, p0.y));

	rect.xMin = std::max(0.0f, std::min(rect.xMin, p1.x));
	rect.yMin = std::max(0.0f, std::min(rect.yMin, p1.y));
	rect.xMax = std::min(frameBuffer.getWidth() - 1.0f, std::max(rect.xMax, p1.x));
	rect.yMax = std::min(frameBuffer.getHeight() - 1.0f, std::max(rect.yMax, p1.y));

	rect.xMin = std::max(0.0f, std::min(rect.xMin, p2.x));
	rect.yMin = std::max(0.0f, std::min(rect.yMin, p2.y));
	rect.xMax = std::min(frameBuffer.getWidth() - 1.0f, std::max(rect.xMax, p2.x));
	rect.yMax = std::min(frameBuffer.getHeight() - 1.0f, std::max(rect.yMax, p2.y));

	Vec3f p;
	for (p.x = rect.xMin; p.x <= rect.xMax; p.x++)
	{
		for (p.y = rect.yMin; p.y <= rect.yMax; p.y++)
		{
			Vec3f b = barycentric(p0, p1, p2, p);
			if (b.x < 0 || b.y < 0 || b.z < 0)
			{
				continue;
			}
			p.z = 0;
			p.z += p0.z * b.x;
			p.z += p1.z * b.y;
			p.z += p2.z * b.z;

			if (frameBuffer.getDepth(p.x, p.y) < p.z)
			{
				// frameBuffer.setDepth(p.x, p.y, p.z);
				// frameBuffer.drawPixel(p.x, p.y, color);
			}
		}
	}
}

Vec3f Graphics::barycentric(Vec3f p0, Vec3f p1, Vec3f p2, Vec3f p)
{
	Vec3f u = Vec3f::cross(Vec3f(p2.x - p0.x, p1.x - p0.x, p0.x - p.x), Vec3f(p2.y - p0.y, p1.y - p0.y, p0.y - p.y));
	if (std::abs(u.z) > 1e-2)
	{
		return Vec3f(1.0 - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
	}

	return Vec3f(-1, 1, 1);
}