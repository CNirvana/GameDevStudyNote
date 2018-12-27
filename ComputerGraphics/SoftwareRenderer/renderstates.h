#pragma once

#include "mat4.hpp"

enum RenderMode
{
	Wireframe,
	Rasterization
};

class RenderStates
{
public:
	static RenderStates& get()
	{
		static RenderStates renderStates;
		return renderStates;
	}

	const Mat4x4& getProjectionMatrix() const { return m_ProjectionMatrix; }
	void setProjectionMatrix(const Mat4x4& projectionMatrix)
	{
		m_ProjectionMatrix = projectionMatrix;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		m_ModelViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
	}

	const Mat4x4& getViewMatrix() const { return m_ViewMatrix; }
	void setViewMatrix(const Mat4x4& viewMatrix)
	{
		m_ViewMatrix = viewMatrix;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		m_ModelViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
	}

	const Mat4x4& getModelMatrix() const { return m_ModelMatrix; }
	void setModelMatrix(const Mat4x4& modelMatrix)
	{
		m_ModelMatrix = modelMatrix;
		m_ModelViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
	}

	const Mat4x4& getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	const Mat4x4& getWorldViewProjectionMatrix() const { return m_ModelViewProjectionMatrix; }

	RenderMode getRenderMode() const { return m_RenderMode; }
	void setRenderMode(RenderMode renderMode) { m_RenderMode = renderMode; }

private:
	Mat4x4 m_ProjectionMatrix;
	Mat4x4 m_ViewMatrix;
	Mat4x4 m_ModelMatrix;
	Mat4x4 m_ViewProjectionMatrix;
	Mat4x4 m_ModelViewProjectionMatrix;
	RenderMode m_RenderMode = RenderMode::Rasterization;
};