#pragma once

#include "utility.h"
#include "texture.h"
#include "shader.h"
#include "model.h"

class Resources
{
public:
	static Resources* getInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new Resources();
		}

		return m_Instance;
	}

	static Texture* loadTexture(const std::string& path, const TextureProperty& textureProperty)
	{
		return getInstance()->loadTextureInternal(path, textureProperty);
	}
	static Shader* loadShaderFromFile(const std::string& name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
	{
		return getInstance()->loadShaderFromFileInternal(name, vertexPath, fragmentPath, geometryPath);
	}
	static Shader* loadShaderFromSource(const std::string& name, const char* vSource, const char* fSource, const char* gSource = nullptr)
	{
		return getInstance()->loadShaderFromSourceInternal(name, vSource, fSource, gSource);
	}
	static Shader* getShader(const std::string& name);

	void finalize();

protected:
	Texture* loadTextureInternal(const std::string& path, const TextureProperty& textureProperty);
	Shader* loadShaderFromFileInternal(const std::string& name, const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	Shader* loadShaderFromSourceInternal(const std::string& name, const char* vSource, const char* fSource, const char* gSource);

private:
	static Resources* m_Instance;

	std::unordered_map<std::string, Texture*> m_Textures;
	std::unordered_map<std::string, Shader*> m_Shaders;
};