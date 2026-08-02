#pragma once
#include "Model.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity
{
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    Model *model;
    bool isDirty;
    glm::mat4 modelMatrix;
    glm::mat4 generateModelMatrix();

public:
    Entity(Model *loadedModel, glm::vec3 position = glm::vec3(0.0), glm::vec3 rotation = glm::vec3(0.0), glm::vec3 scale = glm::vec3(1.0));
    glm::mat4 getModelMatrix();

    void setPosition(glm::vec3 newPosition);
    void setRotation(glm::vec3 newRotation);
    void setScale(glm::vec3 newScale);

    void translate(glm::vec3 translation);
    void rotate(glm::vec3 rotation);
    void scaleBy(glm::vec3 scaleFactors);

    void Draw(Shader &shader);
};