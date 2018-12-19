#pragma once

#include "cubemap.h"
#include "resources.h"
#include "idrawable.h"
#include "quad.h"
#include "framebuffer.h"
#include "depthmap.h"

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	glm::mat4 getProjectionMatrix() const { return m_ProjectionMatrix; }
	void setProjectionMatrix(const glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }
	glm::mat4 getViewMatrix() const { return m_ViewMatrix; }
	void setViewMatrix(const glm::mat4& viewMatrix) { m_ViewMatrix = viewMatrix; }
	glm::vec3 getCameraPos() const { return m_CameraPos; }
	void setCameraPos(const glm::vec3& cameraPos) { m_CameraPos = cameraPos; }
	void setSkybox(Cubemap* skybox) { m_Skybox = skybox; }
	glm::vec4 getClearColor() const { return m_ClearColor; }
	void setClearColor(const glm::vec4& clearColor)
	{
		glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
		m_ClearColor = clearColor;
	}

	void draw(IDrawable& drawable) const;
	void drawWithShader(IDrawable& drawable, Shader* shader) const;
	void drawSkybox() const;
	void bindFrameBuffer(const FrameBuffer& frameBuffer) const;
	void drawFrameBuffer(const FrameBuffer& frameBuffer, Shader* shader) const;

	void beginSampleDepthMap();
	void endSampleDepthMap();

	void clear(bool color = true, bool depth = true, bool stencil = true) const;

	void enableDepthTest(bool enable) const;
	void setDepthWrite(bool write) const;
	void setDepthFunc(DepthTestFunc func) const;

	void enableStencilTest(bool enable) const;
	void setStencilMask(unsigned int mask = 0xff) const;
	void setStencilFunc(StencilFunc func, int ref, unsigned int mask = 0xff) const;
	void setStencilOp(StencilOp stencilFail = StencilOp::Keep, StencilOp depthFail = StencilOp::Keep, StencilOp depthPass = StencilOp::Keep) const;

	void enableBlend(bool enable) const;
	void setBlendFunc(BlendFunc srcFactor, BlendFunc dstFactor) const;
	void setBlendEquation(BlendEquation mode) const;

	void enableCulling(bool enable) const;
	void setCullFace(CullFace mode = CullFace::Back) const;
	void setFontFace(FrontFace mode = FrontFace::CCW) const;

	void enablePolygonMode(bool enable) const;
	void enableMSAA(bool enable) const;

private:
	Shader* m_SkyboxShader;
	Cubemap* m_Skybox;
	DepthMap* m_DepthMap;

	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::vec3 m_CameraPos;
	Quad m_OffscreenQuad;
	glm::vec4 m_ClearColor;

};