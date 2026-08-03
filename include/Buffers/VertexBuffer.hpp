#pragma once
#include <glad/glad.h>
#include <cstddef>

class VertexBuffer
{
private:
    unsigned int bufferId;

public:
    VertexBuffer();
    VertexBuffer(const size_t size, const void *data, GLenum drawType);

    VertexBuffer(const VertexBuffer &other) = delete;
    VertexBuffer &operator=(const VertexBuffer &other) = delete;

    VertexBuffer(VertexBuffer &&other) noexcept;
    VertexBuffer &operator=(VertexBuffer &&other) noexcept;

    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};