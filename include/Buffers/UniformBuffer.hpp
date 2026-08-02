#pragma once
#include <glad/glad.h>
#include <cstddef>

class UniformBuffer
{
    private:
    unsigned int bufferId;

    public:
    UniformBuffer();
    // Size must be in bytes
    UniformBuffer(const size_t size, const void *data, const unsigned int drawType);
    ~UniformBuffer();

    void bind() const;
    void unbind() const;
};