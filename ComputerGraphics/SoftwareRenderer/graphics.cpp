#include "graphics.h"

void Graphics::drawLine(Vec2i p0, Vec2i p1, TGAImage& image, const TGAColor& color)
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
			image.set(y, x, color);
		}
		else
		{
			image.set(x, y, color);
		}

		error += derror;
		if (error > dx)
		{
			y += (p1.y > p0.y ? 1 : -1);
			error -= dx * 2;
		}
	}
}

void Graphics::drawTriangle(Vec2i p0, Vec2i p1, Vec2i p2, TGAImage& image, const TGAColor& color)
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
			image.set(j, p0.y + i, color);
		}
	}
	/*for (int y = p0.y; y <= p1.y; y++)
	{
		int segmentHeight = p1.y - p0.y + 1;
		float alpha = (float)(y - p0.y) / totalHeight;
		float beta = (float)(y - p0.y) / segmentHeight;
		Vec2i A = p0 + Vec2i(p2mp0.x * alpha, p2mp0.y * alpha);
		Vec2i B = p0 + Vec2i(p1mp0.x * beta, p1mp0.y * beta);
		if (A.x > B.x)
		{
			std::swap(A, B);
		}
		for (int j = A.x; j <= B.x; j++)
		{
			image.set(j, y, color);
		}
	}
	for (int y = p1.y; y <= p2.y; y++)
	{
		int segmentHeight = p2.y - p1.y + 1;
		float alpha = (float)(y - p0.y) / totalHeight;
		float beta = (float)(y - p1.y) / segmentHeight;
		Vec2i A = p0 + Vec2i(p2mp0.x * alpha, p2mp0.y * alpha);
		Vec2i B = p1 + Vec2i(p2mp1.x * beta, p1mp0.y * beta);
		if (A.x > B.x)
		{
			std::swap(A, B);
		}
		for (int j = A.x; j <= B.x; j++)
		{
			image.set(j, y, color);
		}
	}*/
}