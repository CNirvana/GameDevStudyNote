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

void TinyGL::drawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	VertIn vertIn1(v1);
	VertOut vertOut1;
	m_Shader->vert(&vertIn1, &vertOut1);

	VertIn vertIn2(v2);
	VertOut vertOut2;
	m_Shader->vert(&vertIn2, &vertOut2);

	VertIn vertIn3(v3);
	VertOut vertOut3;
	m_Shader->vert(&vertIn3, &vertOut3);

	vertOut1.position /= vertOut1.position.w;
	vertOut2.position /= vertOut2.position.w;
	vertOut3.position /= vertOut3.position.w;

	int width = m_FrameBuffer->getWidth();
	int height = m_FrameBuffer->getHeight();
	vertOut1.position.x = (vertOut1.position.x + 1) * 0.5 * width;
	vertOut1.position.y = (1 - vertOut1.position.y) * 0.5 * height;
	vertOut2.position.x = (vertOut2.position.x + 1) * 0.5 * width;
	vertOut2.position.y = (1 - vertOut2.position.y) * 0.5 * height;
	vertOut3.position.x = (vertOut3.position.x + 1) * 0.5 * width;
	vertOut3.position.y = (1 - vertOut3.position.y) * 0.5 * height;

	switch (RenderStates::get().getRenderMode())
	{
		case RenderMode::Rasterization:
		{
			rasterization(vertOut1, vertOut2, vertOut3);
		}
		break;
		case RenderMode::Wireframe:
		{
			Vec2i p1 = Vec2i(vertOut1.position.x, vertOut1.position.y);
			Vec2i p2 = Vec2i(vertOut2.position.x, vertOut2.position.y);
			Vec2i p3 = Vec2i(vertOut3.position.x, vertOut3.position.y);

			drawLine(p1, p2, Color::white);
			drawLine(p2, p3, Color::white);
			drawLine(p3, p1, Color::white);
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

void TinyGL::rasterization(const VertOut& v1, const VertOut& v2, const VertOut& v3)
{
	Vec4f p1 = v1.position;
	Vec4f p2 = v2.position;
	Vec4f p3 = v3.position;

	int width = m_FrameBuffer->getWidth();
	int height = m_FrameBuffer->getHeight();

	float area = edgeFunction(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
	float invArea = 1.0f / area;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			Vec3f p(i + 0.5f, j + 0.5f, 0);
			float w0 = edgeFunction(p2.x, p2.y, p3.x, p3.y, p.x, p.y);
			float w1 = edgeFunction(p3.x, p3.y, p1.x, p1.y, p.x, p.y);
			float w2 = edgeFunction(p1.x, p1.y, p2.x, p2.y, p.x, p.y);

			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				w0 *= invArea;
				w1 *= invArea;
				w2 *= invArea;

				VertOut fragIN;
				fragIN.color.r = w0 * v1.color.r + w1 * v2.color.r + w2 * v3.color.r;
				fragIN.color.g = w0 * v1.color.g + w1 * v2.color.g + w2 * v3.color.g;
				fragIN.color.b = w0 * v1.color.b + w1 * v2.color.b + w2 * v3.color.b;

				Color color = m_Shader->frag(&fragIN);
				m_FrameBuffer->setPixel(i, j, color);
			}
		}
	}
}

void TinyGL::wireframe(const VertOut& v1, const VertOut& v2, const VertOut& v3)
{

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