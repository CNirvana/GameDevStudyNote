#include "vertexarray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
}

inline
void VertexArray::bind() const
{
    glBindVertexArray(m_ID);
}

inline
void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    bind();
    vertexBuffer->bind();

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // TexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    // Tangent
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    glEnableVertexAttribArray(3);

    // Bitangent
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    glEnableVertexAttribArray(4);

    m_VertexBuffer = vertexBuffer;
}

void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    bind();
    indexBuffer->bind();
    m_IndexBuffer = indexBuffer;
}