#pragma once
#include <glad/glad.h>
#include <cstddef>

class UniformBuffer
{
private:
    unsigned int bufferId;

public:
    // Prevent the compiler from ever copying this object and double-deleting the buffer
    UniformBuffer(const UniformBuffer &) = delete;
    UniformBuffer &operator=(const UniformBuffer &) = delete;

    // Size must be in bytes
    UniformBuffer(const size_t size, const void *data, const unsigned int drawType);

    UniformBuffer(UniformBuffer &&other) noexcept;
    UniformBuffer &operator=(UniformBuffer &&other) noexcept;

    ~UniformBuffer();

    void bind() const;
    void unbind() const;

    void setBindingPoint(unsigned int bindingPoint) const;
    // Injects specific data into a specific memory offset
    void updateData(size_t offset, size_t size, const void *data) const;
};