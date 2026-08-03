#pragma once
#include <glad/glad.h>
#include "Buffers/VertexBuffer.hpp"

class VertexArray
{
private:
    unsigned int arrayId;

public:
    VertexArray();

    VertexArray(const VertexArray &other) = delete;
    VertexArray &operator=(const VertexArray &other) = delete;

    VertexArray(VertexArray &&other) noexcept;
    VertexArray &operator=(VertexArray &&other) noexcept;
    
    ~VertexArray();

    void linkAttribute(VertexBuffer &VBO, unsigned int layout, unsigned int numComponents, GLenum type, bool normalised, int stride, void *offset);

    void bind() const;
    void unbind() const;
};