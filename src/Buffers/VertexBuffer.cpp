#include "Buffers/VertexBuffer.hpp"

VertexBuffer::VertexBuffer()
{
    this->bufferId = 0;
}

VertexBuffer::VertexBuffer(const size_t size, const void *data, GLenum drawType)
{
    glGenBuffers(1, &bufferId);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, drawType);
    unbind();
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &bufferId);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}
void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}