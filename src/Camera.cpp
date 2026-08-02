#include "Camera.hpp"

void Camera::moveForward(float distance)
{
    this->position += this->front * distance;
    this->isViewDirty = true;
}

void Camera::moveRight(float distance)
{
    // The Cross Product calculates a vector perfectly perpendicular to front and up (pointing right)
    glm::vec3 right = glm::normalize(glm::cross(this->front, this->up));
    this->position += right * distance;
    this->isViewDirty = true;
}

void Camera::moveUp(float distance)
{
    this->position += this->up * distance;
    this->isViewDirty = true;
}

void Camera::updateCameraVectors()
{
    // New Front vector using Euler Angles
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    newFront.y = sin(glm::radians(this->pitch));
    newFront.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    // Normalize it so movement does not slow down/speed up
    this->front = glm::normalize(newFront);

    this->isViewDirty = true;
}

glm::mat4 Camera::generateViewMatrix()
{
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

glm::mat4 Camera::generateProjectionMatrix()
{
    return glm::perspective(glm::radians(this->fov), this->aspectRatio, this->nearPlane, this->farPlane);
}

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float fov, float aspectRatio, float nearPlane, float farPlane)
    : position(position), front(front), up(up), yaw(-90.0), pitch(0.0), fov(fov), aspectRatio(aspectRatio), nearPlane(nearPlane), farPlane(farPlane),
      isViewDirty(true), isProjectionDirty(true), viewMatrix(generateViewMatrix()), projectionMatrix(generateProjectionMatrix()), UBO(2 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW)
{
    // Transmit view and projection matrices to layout(binding = 0)
    this->UBO.setBindingPoint(0);
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

void Camera::translate(glm::vec3 translation)
{
    moveForward(translation.z);
    moveUp(translation.y);
    moveRight(translation.x);

    this->isViewDirty = true;
}

void Camera::rotate(float yawOffset, float pitchOffset)
{
    this->yaw += yawOffset;
    this->pitch += pitchOffset;

    // Constrain the pitch
    if (this->pitch > 89.0f)
        this->pitch = 89.0f;
    if (this->pitch < -89.0f)
        this->pitch = -89.0f;

    this->updateCameraVectors();
}

void Camera::Update()
{
    if (this->isViewDirty)
    {
        this->viewMatrix = generateViewMatrix();
        this->UBO.updateData(0, sizeof(glm::mat4), glm::value_ptr(this->viewMatrix));
        this->isViewDirty = false;
    }

    if (this->isProjectionDirty)
    {
        this->projectionMatrix = generateProjectionMatrix();
        this->UBO.updateData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(this->projectionMatrix));
        this->isProjectionDirty = false;
    }
}