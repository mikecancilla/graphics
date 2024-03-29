#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
    unsigned int m_vertexArrayObjectID;

public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void UnBind() const;
};