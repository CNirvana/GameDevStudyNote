#include "resources.h"

Resources* Resources::m_Instance = nullptr;

Texture* Resources::loadTextureInternal(const std::string& path, const TextureProperty& textureProperty)
{
	if (m_Textures.find(path) == m_Textures.end())
	{
		Texture* texture = new Texture(path, textureProperty);
		m_Textures.insert(std::make_pair(path, texture));
	}

	return m_Textures[path];
}

Shader* Resources::loadShaderFromFileInternal(const std::string& name, const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	if (m_Shaders.find(name) == m_Shaders.end())
	{
		Shader* shader = new Shader();
		shader->loadFromFile(vertexPath, fragmentPath, geometryPath);
		m_Shaders.insert(std::make_pair(name, shader));
	}

	return m_Shaders[name];
}

Shader* Resources::loadShaderFromSourceInternal(const std::string& name, const char* vSource, const char* fSource, const char* gSource)
{
	if (m_Shaders.find(name) == m_Shaders.end())
	{
		Shader* shader = new Shader();
		shader->loadFromSource(vSource, fSource, gSource);
		m_Shaders.insert(std::make_pair(name, shader));
	}

	return m_Shaders[name];
}

Shader* Resources::getShader(const std::string& name)
{
	if (getInstance()->m_Shaders.find(name) == getInstance()->m_Shaders.end())
	{
		return nullptr;
	}

	return getInstance()->m_Shaders[name];
}

void Resources::finalize()
{
	for (auto it = m_Textures.begin(); it != m_Textures.end(); it++)
	{
		it->second->release();
		SAFE_DELETE(it->second);
	}

	for (auto it = m_Shaders.begin(); it != m_Shaders.end(); it++)
	{
		it->second->release();
		SAFE_DELETE(it->second);
	}

	m_Textures.clear();
	m_Shaders.clear();
}