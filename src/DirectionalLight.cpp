#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(glm::vec4 position, glm::vec4 color, Entity *entity)
    : position(position), color(color), UBO(2 * sizeof(glm::vec4), NULL, GL_STATIC_DRAW), entity(entity)
{
    if (entity != nullptr)
    {
        this->entity->setPosition(this->position);
    }
    this->UBO.setBindingPoint(3);
    this->UBO.updateData(offsetof(DirectionalLight, position), sizeof(glm::vec4), &this->position);
    this->UBO.updateData(offsetof(DirectionalLight, color), sizeof(glm::vec4), &this->color);
}

void DirectionalLight::setPosition(glm::vec4 position)
{
    this->position = position;
    this->entity->setPosition(position);
    this->UBO.updateData(offsetof(DirectionalLight, position), sizeof(glm::vec4), &this->position);
}

void DirectionalLight::setColor(glm::vec4 color)
{
    this->color = color;
    this->UBO.updateData(offsetof(DirectionalLight, color), sizeof(glm::vec4), &this->color);
}

void DirectionalLight::translate(glm::vec4 translation)
{
    this->position += translation;
    if (entity != nullptr)
    {
        this->entity->setPosition(this->position);
    }
    this->UBO.updateData(offsetof(DirectionalLight, position), sizeof(glm::vec4), &this->position);
}

void DirectionalLight::Draw(Shader &shader)
{
    if (entity != nullptr)
    {
        this->entity->Draw(shader);
    }
}