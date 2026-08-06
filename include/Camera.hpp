#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Buffers/UniformBuffer.hpp"

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    float yaw;
    float pitch;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    bool isViewDirty;
    bool isProjectionDirty;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    glm::mat4 generateViewMatrix();
    glm::mat4 generateProjectionMatrix();

    UniformBuffer UBO;
    void updateCameraVectors();

public:
    Camera(glm::vec3 position = glm::vec3(0.0, 0.0, 1.0), glm::vec3 front = glm::vec3(0.0, 0.0, -1.0), glm::vec3 up = glm::vec3(0.0, 1.0, 0.0),
           float fov = 45.0, float aspectRatio = 16.0 / 9.0, float nearPlane = 0.1, float farPlane = 2000.0);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void setPosition(glm::vec3 newPosition);
    void setFront(glm::vec3 newFront);
    void setUp(glm::vec3 newUp);

    void setFov(float newFov);
    void setAspectRatio(float newAspectRatio);
    void setNearPlane(float newNearPlane);
    void setFarPlane(float newFarPlane);

    void moveForward(float distance);
    void moveRight(float distance);
    void moveUp(float distance);
    void translate(glm::vec3 translation);
    void rotate(float yawOffset, float pitchOffset);

    void Update();
};