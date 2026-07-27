#include "Buffers/VertexBuffer.hpp"

VertexBuffer::VertexBuffer(const size_t size, const void* data, GLenum drawType) {
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, size, data, drawType);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &bufferId);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}
void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}