#include "Buffers/VertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &arrayId);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &arrayId);
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