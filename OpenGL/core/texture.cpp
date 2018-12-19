#include "texture.h"
#include <iostream>

Texture::Texture(const std::string& path, const TextureProperty& textureProperty)
	: m_Path(path), m_Property(textureProperty)
{
	GL_CALL(glGenTextures(1, &m_ID));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ID));

	auto filter = textureProperty.filterMode;
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toGLTextureWrapMode(textureProperty.wrapMode)));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toGLTextureWrapMode(textureProperty.wrapMode)));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toGLTextureFilterMode(filter)));
	if (filter == TextureFilterMode::Trilinear) filter = TextureFilterMode::Bilinear;
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toGLTextureFilterMode(filter)));

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
	if (data != nullptr)
	{
		if (m_Channels == 3)
		{
			GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
		}
		else
		{
			GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
		}

		if (textureProperty.mipmap)
		{
			GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
		}
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

	stbi_image_free(data);
}