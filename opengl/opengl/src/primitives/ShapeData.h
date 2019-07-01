#pragma once
#include <GL/glew.h>
#include "Primitives/Vertex.h"

struct ShapeData
{
    ShapeData() :
        vertices(nullptr),
        numVertices(0),
        indices(nullptr),
        numIndices(0) {}

    Vertex* vertices;
    GLuint numVertices;
    GLushort* indices;
    GLuint numIndices;

    GLsizeiptr vertexBufferSize() const
    {
        return numVertices * sizeof(Vertex);
    }

    GLsizeiptr indexBufferSize() const
    {
        return numIndices * sizeof(GLushort);
    }

    void cleanup()
    {
        delete [] vertices;
        delete [] indices;
        numVertices = numIndices = 0;
    }
};
