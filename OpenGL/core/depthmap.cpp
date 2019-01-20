#include "depthmap.h"

DepthMap::DepthMap(int width, int height, TextureWrapMode wrapMode, TextureFilterMode filterMode)
	: m_Width(width), m_Height(height)
{
	GL_CALL(glGenFramebuffers(1, &m_DepthMapFBO));

	GL_CALL(glGenTextures(1, &m_DepthMap));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_DepthMap));
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toGLTextureWrapMode(wrapMode)));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toGLTextureWrapMode(wrapMode)));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toGLTextureFilterMode(filterMode)));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toGLTextureFilterMode(filterMode)));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

	GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO));
	GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthMap, 0));
	GL_CALL(glDrawBuffer(GL_NONE));
	GL_CALL(glReadBuffer(GL_NONE));
	GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void DepthMap::release()
{
	/*GL_CALL(glDeleteTextures(1, &m_DepthMap));
	GL_CALL(glDeleteFramebuffers(1, &m_DepthMapFBO));*/
}

void DepthMap::beginSample() const
{
	GL_CALL(glViewport(0, 0, m_Width, m_Height));
	GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO));
	GL_CALL(glClear(GL_DEPTH_BUFFER_BIT));
}

void DepthMap::endSample() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}