#pragma once

#include <vector>
#include <algorithm>
#include "vertex.h"
#include "framebuffer.h"
#include "ishader.h"
#include "renderstates.h"

enum ClearFlags
{
	ColorBuffer = 1 << 0,
	DepthBuffer = 1 << 1,
	StencilBuffer = 1 << 2
};

class TinyGL
{
public:
	TinyGL() : m_FrameBuffer(nullptr), m_Shader(nullptr), m_ClearColor(Color::clear) {}
	~TinyGL()
	{
		if (m_FrameBuffer != nullptr) delete m_FrameBuffer;
		if (m_Shader != nullptr) delete m_Shader;
	}
	void initialize(int width, int height);
	void setViewProjectionMatrix(const Mat4x4& viewMatrix, const Mat4x4& projectionMatrix)
	{
		RenderStates::get().setViewMatrix(viewMatrix);
		RenderStates::get().setProjectionMatrix(projectionMatrix);
	}
	void bindTexture(Texture* texture, int slot)
	{
		RenderStates::get().bindTexture(texture, slot);
	}

	void drawElements(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Mat4x4& transform);
	void drawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void drawLine(Vec2i p0, Vec2i p1, const Color& color);
	void clear(int flags);

	void bindShader(IShader* shader) { m_Shader = shader; }

	const FrameBuffer* getFrameBuffer() const { return m_FrameBuffer; }

	const Color& getClearColor() const { return m_ClearColor; }
	void setClearColor(const Color& color) { m_ClearColor = color; }

private:
	void rasterization(const VertOut& v0, const VertOut& v1, const VertOut& v2);
	void wireframe(const VertOut& v0, const VertOut& v1, const VertOut& v2);
	inline float edgeFunction(float Ax, float Ay, float Bx, float By, float Cx, float Cy) const; // CCW
	bool inTriangle(float Ax, float Ay, float Bx, float By, float Cx, float Cy, float Px, float Py) const;
	void scanline(Vec2i p0, Vec2i p1, Vec2i p2, const Color& color);
	void interpolate(const VertOut& v0, const VertOut& v1, const VertOut& v2, float w0, float w1, float w2, VertOut& out) const;
	inline float computeDepth(float invZ0, float w0, float invZ1, float w1, float invZ2, float w2) const;
	inline bool clipping(const Vec4f& v) const;
	void clipToNDC(VertOut& v) const;

	IShader* m_Shader;
	FrameBuffer* m_FrameBuffer;
	Color m_ClearColor;
};