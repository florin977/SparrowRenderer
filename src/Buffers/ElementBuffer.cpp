#include "Buffers/ElementBuffer.hpp"

ElementBuffer ::ElementBuffer()
{
    this->bufferId = 0;
}

ElementBuffer::ElementBuffer(ElementBuffer &&other) noexcept
    : bufferId(other.bufferId), indicesCount(other.indicesCount)
{
    other.bufferId = 0;
    other.indicesCount = 0;
}

ElementBuffer &ElementBuffer::operator=(ElementBuffer &&other) noexcept
{
    if (this != &other)
    {
        if (this->bufferId != 0)
        {
            glDeleteBuffers(1, &this->bufferId);
        }

        this->bufferId = other.bufferId;
        this->indicesCount = other.indicesCount;

        other.bufferId = 0;
        other.indicesCount = 0;
    }
    return *this;
}

ElementBuffer::ElementBuffer(const unsigned int *data, unsigned int indicesCount)
{
    this->indicesCount = indicesCount;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
    if (this->bufferId != 0)
    {
        glDeleteBuffers(1, &bufferId);
    }
}

void ElementBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void ElementBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int ElementBuffer::getIndicesCount() const
{
    return indicesCount;
}