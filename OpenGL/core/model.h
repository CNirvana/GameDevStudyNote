#pragma once

#include "mesh.h"

class Model : public IDrawable
{
public:
	Model(const std::string& path, Shader* shader);
	virtual ~Model();

	virtual void drawWithShader(const Renderer& renderer, Shader* shader) override;
	void drawInstanced(const Shader& shader, int amount) const;
	const std::vector<Mesh*>& getMeshes() const { return m_Meshes; }

protected:
	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type);
	TextureType convertAssimpTextureType(aiTextureType type);

private:
	std::vector<Mesh*> m_Meshes;
	std::vector<Texture*> m_Textures;
	std::string m_ModelDirectory;
};