#pragma once

#include "common.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;
    void setVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
    void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer);
    const Ref<VertexBuffer>& getVertexBuffer() const { return m_VertexBuffer; }
    const Ref<IndexBuffer>& getIndexBuffer() const { return m_IndexBuffer; }

    unsigned int getID() const { return m_ID; }

private:
    unsigned int m_ID;
    Ref<VertexBuffer> m_VertexBuffer;
    Ref<IndexBuffer> m_IndexBuffer;
};