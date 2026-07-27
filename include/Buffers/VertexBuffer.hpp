#pragma once
#include <glad/glad.h>
#include <cstddef>

class VertexBuffer
{
private:
    unsigned int bufferId;

public:
    VertexBuffer(const size_t size, const void *data, GLenum drawType);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};