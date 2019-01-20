#pragma once

#include "common.h"
#include "iglresource.h"

class FrameBuffer : public IGLResource
{
public:
	FrameBuffer(int width, int height, TextureWrapMode wrapMode = TextureWrapMode::Clamp, TextureFilterMode filterMode = TextureFilterMode::Bilinear);

	void bind() const { GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO)); }
	void unbind() const { GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0)); }
	void bindColorBuffer() const { GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ColorBuffer)); }
	int getWidth() const { return m_Width; }
	int getHeight() const { return m_Height; }

	virtual void release() override;

private:
	unsigned int m_FBO;
	unsigned int m_ColorBuffer;
	unsigned int m_RBO;

	int m_Width;
	int m_Height;
};

