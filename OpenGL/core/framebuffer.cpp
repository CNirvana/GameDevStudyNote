#include "framebuffer.h"

FrameBuffer::FrameBuffer(int width, int height, TextureWrapMode wrapMode, TextureFilterMode filterMode)
    : m_Width(width), m_Height(height)
{
    GL_CALL(glGenFramebuffers(1, &m_FBO));
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO));

    GL_CALL(glGenTextures(1, &m_ColorBuffer));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ColorBuffer));
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toGLTextureWrapMode(wrapMode)));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toGLTextureWrapMode(wrapMode)));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toGLTextureFilterMode(filterMode)));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toGLTextureFilterMode(filterMode)));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

    GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorBuffer, 0));

    GL_CALL(glGenRenderbuffers(1, &m_RBO));
    GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_RBO));
    GL_CALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
    GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));

    GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO));

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }

    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::release()
{

}