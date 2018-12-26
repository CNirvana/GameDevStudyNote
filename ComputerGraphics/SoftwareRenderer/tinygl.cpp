#include "tinygl.h"

void TinyGL::initialize(int width, int height)
{
	if (m_FrameBuffer != nullptr) delete m_FrameBuffer;
	m_FrameBuffer = new FrameBuffer(width, height);

	if (m_Shader != nullptr) delete m_Shader;
	m_Shader = new DefaultShader();
}

void TinyGL::drawElements(const std::vector<Vertex> vertices, const std::vector<int> indices, const Mat4x4& transform)
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

	rasterization(vertOut1, vertOut2, vertOut3);
}

void TinyGL::rasterization(const VertOut& v1, const VertOut& v2, const VertOut& v3)
{
	Vec4f p1 = v1.position;
	p1 /= p1.w;
	Vec4f p2 = v2.position;
	p2 /= p2.w;
	Vec4f p3 = v3.position;
	p3 /= p3.w;

	int width = m_FrameBuffer->getWidth();
	int height = m_FrameBuffer->getHeight();
	p1.x = (p1.x + 1) * 0.5 * width;
	p1.y = (1 - p1.y) * 0.5 * height;
	p2.x = (p2.x + 1) * 0.5 * width;
	p2.y = (1 - p2.y) * 0.5 * height;
	p3.x = (p3.x + 1) * 0.5 * width;
	p3.y = (1 - p3.y) * 0.5 * height;

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

void TinyGL::clear(int flags)
{
	if (flags & ClearFlags::ColorBuffer)
	{
		m_FrameBuffer->clearColorBuffer({ 0, 0, 0, 0 });
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