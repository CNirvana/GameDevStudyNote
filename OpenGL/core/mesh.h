#pragma once

#include "texture.h"
#include "shader.h"
#include "idrawable.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

class Mesh : public IGLResource, public IDrawable
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture*> textures;

	Mesh(Shader* shader, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture*>& textures);
	virtual void draw(const Renderer& renderer) override;
	virtual void drawWithShader(const Renderer& renderer, Shader* shader) override;
	void drawInstanced(const Shader& shader, int amount) const;
	void bind() const { glBindVertexArray(m_VAO); }
	void unbind() const { glBindVertexArray(0); }

	virtual void release() override;

protected:
	void setupMesh();
	void bindTextures(Shader* shader) const;
	void unbindTextures() const { glBindTexture(GL_TEXTURE_2D, 0); }

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

};