#pragma once

#include "iglresource.h"
#include "common.h"

class DepthMap : IGLResource
{
public:
	DepthMap(int width = 1024, int height = 1024, TextureWrapMode wrapMode = TextureWrapMode::Clamp, TextureFilterMode filterMode = TextureFilterMode::Bilinear);

	virtual void release() override;

	void beginSample() const;
	void endSample() const;

private:
	unsigned int m_DepthMapFBO;
	unsigned int m_DepthMap;

	int m_Width;
	int m_Height;
};