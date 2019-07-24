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
    void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
    void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
    const std::shared_ptr<VertexBuffer>& getVertexBuffer() const { return m_VertexBuffer; }
    const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return m_IndexBuffer; }

    unsigned int getID() const { return m_ID; }

private:
    unsigned int m_ID;
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
};