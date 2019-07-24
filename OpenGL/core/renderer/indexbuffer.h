#pragma once

#include "common.h"

class IndexBuffer
{
public:
    IndexBuffer(const std::vector<unsigned int>& indices);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    unsigned int getID() const { return m_ID; }
    unsigned int getCount() const { return m_Count; }

private:
    unsigned int m_ID;
    unsigned int m_Count;
};