#pragma once
#include <glm/glm.hpp>
#include "Buffers/UniformBuffer.hpp"
#include "Entity.hpp"

class DirectionalLight
{
private:
    glm::vec4 position;
    glm::vec4 color;
    UniformBuffer UBO;
    Entity *entity;

public:
    DirectionalLight(glm::vec4 position = glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec4 color = glm::vec4(1.0), Entity *entity = nullptr);
    void setPosition(glm::vec4 position);
    void setColor(glm::vec4 color);
    void translate(glm::vec4 translation);

    void Draw(Shader &shader);
};