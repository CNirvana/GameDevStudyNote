#pragma once

#include "texture.h"
#include "shader.h"
#include "idrawable.h"
#include "renderer/vertexarray.h"

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
    void bind() const { m_VertexArray->bind(); }
    void unbind() const { m_VertexArray->unbind(); }

    virtual void release() override;

protected:
    void setupMesh();
    void bindTextures(Shader* shader) const;
    void unbindTextures() const { glBindTexture(GL_TEXTURE_2D, 0); }

private:
    std::shared_ptr<VertexArray> m_VertexArray;
};