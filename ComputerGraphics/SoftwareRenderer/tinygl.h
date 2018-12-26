#pragma once

#include <vector>
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
	TinyGL() : m_FrameBuffer(nullptr), m_Shader(nullptr) {}
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

	void drawElements(const std::vector<Vertex> vertices, const std::vector<int> indices, const Mat4x4& transform);
	void drawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
	void clear(int flags);

	void bindShader(IShader* shader) { m_Shader = shader; }

	const FrameBuffer* getFrameBuffer() const { return m_FrameBuffer; }

private:
	void rasterization(const VertOut& v1, const VertOut& v2, const VertOut& v3);
	inline float edgeFunction(float Ax, float Ay, float Bx, float By, float Cx, float Cy); // CCW
	bool inTriangle(float Ax, float Ay, float Bx, float By, float Cx, float Cy, float Px, float Py);

	IShader* m_Shader;
	FrameBuffer* m_FrameBuffer;
};