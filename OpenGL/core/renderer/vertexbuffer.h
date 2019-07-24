#pragma once

#include "common.h"
#include "vertex.h"

class VertexBuffer
{
public:
    VertexBuffer(const std::vector<Vertex>& vertices);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

    unsigned int getID() const { return m_ID; }

private:
    unsigned int m_ID;
};