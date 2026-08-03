#include "Buffers/UniformBuffer.hpp"

UniformBuffer::UniformBuffer(const size_t size, const void *data, const unsigned int drawType)
{
    glGenBuffers(1, &this->bufferId);
    this->bind();
    glBufferData(GL_UNIFORM_BUFFER, size, data, drawType);
    this->unbind();
}

UniformBuffer::UniformBuffer(UniformBuffer &&other) noexcept
    : bufferId(other.bufferId)
{
    other.bufferId = 0;
}

UniformBuffer &UniformBuffer::operator=(UniformBuffer &&other) noexcept
{
    if (this != &other)
    {
        if (this->bufferId != 0)
        {
            glDeleteBuffers(1, &this->bufferId);
        }

        this->bufferId = other.bufferId;
        other.bufferId = 0;
    }
    return *this;
}

UniformBuffer::~UniformBuffer()
{
    if (this->bufferId != 0)
    {
        glDeleteBuffers(1, &this->bufferId);
    }
}

void UniformBuffer::bind() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, this->bufferId);
}
void UniformBuffer::unbind() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::setBindingPoint(unsigned int bindingPoint) const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, this->bufferId);
}

void UniformBuffer::updateData(size_t offset, size_t size, const void *data) const
{
    this->bind();
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    this->unbind();
}