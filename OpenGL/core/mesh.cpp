#include "mesh.h"

Mesh::Mesh(Shader* shader, const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices, const std::vector<Texture*>& _textures)
    : IDrawable(shader), vertices(_vertices), indices(_indices), textures(_textures)
{
    setupMesh();
}

void Mesh::release()
{
}

void Mesh::setupMesh()
{
    std::shared_ptr<VertexBuffer> vertexBuffer;
    vertexBuffer.reset(new VertexBuffer(vertices));

    std::shared_ptr<IndexBuffer> indexBuffer;
    indexBuffer.reset(new IndexBuffer(indices));

    m_VertexArray.reset(new VertexArray());
    m_VertexArray->setVertexBuffer(vertexBuffer);
    m_VertexArray->setIndexBuffer(indexBuffer);
}

void Mesh::bindTextures(Shader* shader) const
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (size_t i = 0; i < textures.size(); i++)
    {
        std::string name;
        if (textures[i]->getTextureType() == TextureType::Diffuse)
            name = "u_texture_diffuse" + std::to_string(diffuseNr++);
        else if (textures[i]->getTextureType() == TextureType::Specular)
            name = "u_texture_specular" + std::to_string(specularNr++);
        else if (textures[i]->getTextureType() == TextureType::Normal)
            name = "u_texture_normal" + std::to_string(normalNr++);
        else if (textures[i]->getTextureType() == TextureType::Height)
            name = "u_texture_height" + std::to_string(heightNr++);

        shader->setInt(name, i);
        textures[i]->bind(i);
    }
}

void Mesh::draw(const Renderer& renderer)
{
    drawWithShader(renderer, m_Shader);
}

void Mesh::drawWithShader(const Renderer& renderer, Shader* shader)
{
    bindTextures(shader);

    m_VertexArray->bind();
    GL_CALL(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
    m_VertexArray->unbind();

    unbindTextures();
}

void Mesh::drawInstanced(const Shader& shader, int amount) const
{
    bindTextures(m_Shader);

    m_VertexArray->bind();
    GL_CALL(glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, amount));
    m_VertexArray->unbind();

    unbindTextures();
}