#pragma once

#include "idrawable.h"
#include "quad.h"

class TransparentObject : public IDrawable
{
public:
    TransparentObject(Shader* shader, Texture* texture) : IDrawable(shader), m_Texture(texture) {}

    virtual void drawWithShader(const Renderer& renderer, Shader* shader) override
    {
        shader->setInt("u_mainTex", 0);
        m_Texture->bind(0);
        m_Mesh.draw();
    }

private:
    Texture* m_Texture;
    Quad m_Mesh;
};