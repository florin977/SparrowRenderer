#include "Buffers/VertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &arrayId);
}

VertexArray::VertexArray(VertexArray &&other) noexcept
    : arrayId(other.arrayId)
{
    other.arrayId = 0;
}

VertexArray &VertexArray::operator=(VertexArray &&other) noexcept
{
    if (this != &other)
    {
        if (this->arrayId != 0)
        {
            glDeleteVertexArrays(1, &this->arrayId);
        }

        this->arrayId = other.arrayId;
        other.arrayId = 0;
    }

    return *this;
}

VertexArray::~VertexArray()
{
    if (this->arrayId != 0)
    {
        glDeleteVertexArrays(1, &arrayId);
    }
}

void VertexArray::linkAttribute(VertexBuffer &VBO, unsigned int layout, unsigned int numComponents, GLenum type, bool normalised, int stride, void *offset)
{
    bind();
    VBO.bind();

    glVertexAttribPointer(layout, numComponents, type, normalised, stride, offset);
    glEnableVertexAttribArray(layout);

    VBO.unbind();
    unbind();
}

void VertexArray::bind() const
{
    glBindVertexArray(arrayId);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}