#include "Camera.hpp"

glm::mat4 Camera::generateViewMatrix()
{
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

glm::mat4 Camera::generateProjectionMatrix()
{
    return glm::perspective(glm::radians(this->fov), this->aspectRatio, this->nearPlane, this->farPlane);
}

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float fov, float aspectRatio, float nearPlane, float farPlane)
    : position(position), front(front), up(up), fov(fov), aspectRatio(aspectRatio), nearPlane(nearPlane), farPlane(farPlane),
      isViewDirty(false), isProjectionDirty(false), viewMatrix(generateViewMatrix()), projectionMatrix(generateProjectionMatrix())
{
}

glm::mat4 Camera::getViewMatrix()
{
    if (isViewDirty)
    {
        this->viewMatrix = generateViewMatrix();
        isViewDirty = false;
    }

    return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
    if (isProjectionDirty)
    {
        this->projectionMatrix = generateProjectionMatrix();
        isProjectionDirty = false;
    }

    return this->projectionMatrix;
}

void Camera::setPosition(glm::vec3 newPosition)
{
    this->position = newPosition;
    isViewDirty = true;
}

void Camera::setFront(glm::vec3 newFront)
{
    this->front = newFront;
    isViewDirty = true;
}

void Camera::setUp(glm::vec3 newUp)
{
    this->up = newUp;
    isViewDirty = true;
}

void Camera::setFov(float newFov)
{
    this->fov = newFov;
    isProjectionDirty = true;
}

void Camera::setAspectRatio(float newAspectRatio)
{
    this->aspectRatio = newAspectRatio;
    isProjectionDirty = true;
}

void Camera::setNearPlane(float newNearPlane)
{
    this->nearPlane = newNearPlane;
    isProjectionDirty = true;
}

void Camera::setFarPlane(float newFarPlane)
{
    this->farPlane = newFarPlane;
    isProjectionDirty = true;
}