#pragma once
#include <glad/glad.h>

class ElementBuffer
{
private:
    unsigned int bufferId;
    unsigned int indicesCount;

public:
    ElementBuffer();
    
    ElementBuffer(const ElementBuffer &other) = delete;
    ElementBuffer& operator=(const ElementBuffer &other) = delete;

    ElementBuffer(ElementBuffer &&other) noexcept;
    ElementBuffer& operator=(ElementBuffer &&other) noexcept;

    ElementBuffer(const unsigned int *data, unsigned int indicesCount);
    ~ElementBuffer();

    void bind() const;
    void unbind() const;

    unsigned int getIndicesCount() const;
};