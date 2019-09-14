#pragma once

#include "iglresource.h"
#include "common.h"
#include "stb_image.h"

struct TextureProperty
{
    TextureType type;
    TextureWrapMode wrapMode;
    TextureFilterMode filterMode;
    bool mipmap;
};

class Texture : IGLResource
{
public:
    Texture(const std::string& path, const TextureProperty& textureProperty);

    void bind(unsigned int slot) const
    {
        GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ID));
    }

    const std::string& getPath() const { return m_Path; }
    TextureType getTextureType() const { return m_Property.type; }

    virtual void release() override { /*GL_CALL(glDeleteTextures(1, &m_ID));*/ }

private:
    std::string m_Path;
    unsigned int m_ID;
    TextureProperty m_Property;
    int m_Width;
    int m_Height;
    int m_Channels;

};