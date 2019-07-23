#pragma once

#include "common.h"

class VertexBuffer
{
public:
    VertexBuffer(float* vertices, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

    unsigned int getID() const { return m_ID; }

private:
    unsigned int m_ID;
};