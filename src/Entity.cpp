#include "Entity.hpp"

glm::mat4 Entity::generateModelMatrix()
{
    glm::mat4 transform = glm::mat4(1.0f);

    transform = glm::translate(transform, this->position);

    transform = glm::rotate(transform, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
    transform = glm::rotate(transform, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw
    transform = glm::rotate(transform, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll

    transform = glm::scale(transform, this->scale);

    return transform;
}

Entity::Entity(Model *loadedModel, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : position(position), rotation(rotation), scale(scale), model(loadedModel), isDirty(false), modelMatrix(generateModelMatrix())
{
}

glm::mat4 Entity::getModelMatrix()
{
    if (isDirty)
    {
        this->modelMatrix = generateModelMatrix();
        isDirty = false;
    }

    return this->modelMatrix;
}

void Entity::setPosition(glm::vec3 newPosition)
{
    this->position = newPosition;
    isDirty = true;
}

void Entity::setRotation(glm::vec3 newRotation)
{
    this->rotation = newRotation;
    isDirty = true;
}

void Entity::setScale(glm::vec3 newScale)
{
    this->scale = newScale;
    isDirty = true;
}

void Entity::translate(glm::vec3 translation)
{
    this->position += translation;
    isDirty = true;
}

void Entity::rotate(glm::vec3 rotation)
{
    this->rotation += rotation;
    isDirty = true;
}

void Entity::scaleBy(glm::vec3 scaleFactors)
{
    this->scale *= scaleFactors;
    isDirty = true;
}

void Entity::Draw(Shader &shader)
{
    // ModelMatrix is at layout(location = 0) always
    shader.setMatrix4(0, this->getModelMatrix());
    this->model->Draw(shader);
}