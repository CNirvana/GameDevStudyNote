#include "tinygl.h"

void TinyGL::initialize(int width, int height)
{
	if (m_FrameBuffer != nullptr) delete m_FrameBuffer;
	m_FrameBuffer = new FrameBuffer(width, height);

	if (m_Shader != nullptr) delete m_Shader;
	m_Shader = new DefaultShader();
}

void TinyGL::drawElements(const std::vector<Vertex>& vertices, const std::vector<int>& indices, const Mat4x4& transform)
{
	RenderStates::get().setModelMatrix(transform);

	for (int i = 0; i < indices.size(); i += 3)
	{
		drawTriangle(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);
	}
}

void TinyGL::drawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	VertIn vertIn0(v0);
	VertOut vertOut0;
	m_Shader->vert(&vertIn0, &vertOut0);

	VertIn vertIn1(v1);
	VertOut vertOut1;
	m_Shader->vert(&vertIn1, &vertOut1);

	VertIn vertIn2(v2);
	VertOut vertOut2;
	m_Shader->vert(&vertIn2, &vertOut2);

	// simple clipping
	if (clipping(vertOut0.position) || clipping(vertOut1.position) || clipping(vertOut2.position))
	{
		return;
	}

	vertOut0.invZ = 1 / vertOut0.position.w;
	vertOut1.invZ = 1 / vertOut1.position.w;
	vertOut2.invZ = 1 / vertOut2.position.w;
	vertOut0.position /= vertOut0.position.w;
	vertOut1.position /= vertOut1.position.w;
	vertOut2.position /= vertOut2.position.w;

	int width = m_FrameBuffer->getWidth() - 1;
	int height = m_FrameBuffer->getHeight() - 1;
	vertOut0.position.x = (vertOut0.position.x + 1) * 0.5 * width;
	vertOut0.position.y = (1 - vertOut0.position.y) * 0.5 * height;
	vertOut1.position.x = (vertOut1.position.x + 1) * 0.5 * width;
	vertOut1.position.y = (1 - vertOut1.position.y) * 0.5 * height;
	vertOut2.position.x = (vertOut2.position.x + 1) * 0.5 * width;
	vertOut2.position.y = (1 - vertOut2.position.y) * 0.5 * height;

	switch (RenderStates::get().getRenderMode())
	{
		case RenderMode::Rasterization:
		{
			rasterization(vertOut0, vertOut1, vertOut2);
		}
		break;
		case RenderMode::Wireframe:
		{
			wireframe(vertOut0, vertOut1, vertOut2);
		}
		break;
		default:
			break;
	}
}

void TinyGL::drawLine(Vec2i p0, Vec2i p1, const Color& color)
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
			m_FrameBuffer->setPixel(y, x, color);
		}
		else
		{
			m_FrameBuffer->setPixel(x, y, color);
		}

		error += derror;
		if (error > dx)
		{
			y += (p1.y > p0.y ? 1 : -1);
			error -= dx * 2;
		}
	}
}

void TinyGL::rasterization(const VertOut& v0, const VertOut& v1, const VertOut& v2)
{
	Vec4f p0 = v0.position;
	Vec4f p1 = v1.position;
	Vec4f p2 = v2.position;

	int width = m_FrameBuffer->getWidth();
	int height = m_FrameBuffer->getHeight();

	float xMin = std::numeric_limits<float>::max();
	float yMin = std::numeric_limits<float>::max();
	float xMax = -std::numeric_limits<float>::max();
	float yMax = -std::numeric_limits<float>::max();

	xMin = std::max(0.0f, std::min(xMin, p0.x));
	yMin = std::max(0.0f, std::min(yMin, p0.y));
	xMax = std::min(width - 1.0f, std::max(xMax, p0.x));
	yMax = std::min(height - 1.0f, std::max(yMax, p0.y));

	xMin = std::max(0.0f, std::min(xMin, p1.x));
	yMin = std::max(0.0f, std::min(yMin, p1.y));
	xMax = std::min(width - 1.0f, std::max(xMax, p1.x));
	yMax = std::min(height - 1.0f, std::max(yMax, p1.y));

	xMin = std::max(0.0f, std::min(xMin, p2.x));
	yMin = std::max(0.0f, std::min(yMin, p2.y));
	xMax = std::min(width - 1.0f, std::max(xMax, p2.x));
	yMax = std::min(height - 1.0f, std::max(yMax, p2.y));

	float area = edgeFunction(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y);
	float invArea = 1.0f / area;
	for (int j = yMin; j < yMax; j++)
	{
		for (int i = xMin; i < xMax; i++)
		{
			Vec3f p(i + 0.5f, j + 0.5f, 0);
			float w0 = edgeFunction(p1.x, p1.y, p2.x, p2.y, p.x, p.y);
			float w1 = edgeFunction(p2.x, p2.y, p0.x, p0.y, p.x, p.y);
			float w2 = edgeFunction(p0.x, p0.y, p1.x, p1.y, p.x, p.y);

			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				w0 *= invArea;
				w1 *= invArea;
				w2 *= invArea;

				float z = computeDepth(v0.invZ, w0, v1.invZ, w1, v2.invZ, w2);
				if (z < m_FrameBuffer->getDepth(i, j))
				{
					m_FrameBuffer->setDepth(i, j, z);

					VertOut fragIN;
					interpolate(v0, v1, v2, w0 * v0.invZ * z, w1 * v1.invZ * z, w2 * v2.invZ * z, fragIN);

					Color color = m_Shader->frag(&fragIN);
					m_FrameBuffer->setPixel(i, j, color);
				}
			}
		}
	}
}

void TinyGL::wireframe(const VertOut& v0, const VertOut& v1, const VertOut& v2)
{
	Vec2i p0 = Vec2i(v0.position.x, v0.position.y);
	Vec2i p1 = Vec2i(v1.position.x, v1.position.y);
	Vec2i p2 = Vec2i(v2.position.x, v2.position.y);

	drawLine(p0, p1, Color::white);
	drawLine(p1, p2, Color::white);
	drawLine(p2, p0, Color::white);
}

void TinyGL::clear(int flags)
{
	if (flags & ClearFlags::ColorBuffer)
	{
		m_FrameBuffer->clearColorBuffer(m_ClearColor);
	}
	if (flags & ClearFlags::DepthBuffer)
	{
		m_FrameBuffer->clearDepthBuffer();
	}
}

float TinyGL::edgeFunction(float Ax, float Ay, float Bx, float By, float Px, float Py)
{
	// return (Px - Ax) * (By - Ay) - (Py - Ay) * (Bx -Ax); // CW to right
	return (Ax - Bx) * (Py - Ay) - (Ay - By) * (Px - Ax); // CCW to left
}

bool TinyGL::inTriangle(float Ax, float Ay, float Bx, float By, float Cx, float Cy, float Px, float Py)
{
	bool inside = true;
	inside &= (edgeFunction(Ax, Ay, Bx, By, Px, Py) >= 0);
	inside &= (edgeFunction(Bx, By, Cx, Cy, Px, Py) >= 0);
	inside &= (edgeFunction(Cx, Cy, Ax, Ay, Px, Py) >= 0);

	return inside;
}

void TinyGL::scanline(Vec2i p0, Vec2i p1, Vec2i p2, const Color& color)
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
			m_FrameBuffer->setPixel(j, p0.y + i, color);
		}
	}
}

void TinyGL::interpolate(const VertOut& v0, const VertOut& v1, const VertOut& v2, float w0, float w1, float w2, VertOut& out)
{
	out.position = v0.position * w0 + v1.position * w1 + v2.position * w2;
	out.color = v0.color * w0 + v1.color * w1 + v2.color * w2;
	out.texCoord = v0.texCoord * w0 + v1.texCoord * w1 + v2.texCoord * w2;
	out.normal = v0.normal * w0 + v1.normal * w1 + v2.normal * w2;
	out.worldPos = v0.worldPos * w0 + v1.worldPos * w1 + v2.worldPos * w2;
}

float TinyGL::computeDepth(float invZ0, float w0, float invZ1, float w1, float invZ2, float w2)
{
	float invZ = invZ0 * w0 + invZ1 * w1 + invZ2 * w2;
	return 1 / invZ;
}

bool TinyGL::clipping(const Vec4f& v)
{
	return (v.x < -v.w || v.x > v.w)
		|| (v.y < -v.w || v.y > v.w)
		|| (v.z < -v.w || v.z > v.w)
		|| (v.w <= 0);
}