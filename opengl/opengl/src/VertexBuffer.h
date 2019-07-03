#pragma once

class VertexBuffer
{
private:
    unsigned int m_bufferID;

public:
    VertexBuffer(const void* data, unsigned int sizeInBytes);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};
