#include "Controllers/CameraController.hpp"

void CameraController::handleMovement()
{
    float speed = this->speed;

    if (this->input->keyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        speed = 2.5 * this->speed;
    }
    else
    {
        speed = this->speed;
    }

    if (this->input->keyPressed(GLFW_KEY_W))
    {
        this->camera->moveForward(speed);
    }
    if (this->input->keyPressed(GLFW_KEY_S))
    {
        this->camera->moveForward(-speed);
    }

    if (this->input->keyPressed(GLFW_KEY_A))
    {
        this->camera->moveRight(-speed);
    }
    if (this->input->keyPressed(GLFW_KEY_D))
    {
        this->camera->moveRight(speed);
    }

    if (this->input->keyPressed(GLFW_KEY_SPACE))
    {
        this->camera->moveUp(speed);
    }
    if (this->input->keyPressed(GLFW_KEY_LEFT_CONTROL))
    {
        this->camera->moveUp(-speed);
    }
}
void CameraController::handleRotation()
{
    this->camera->rotate(this->input->getMouseOffsetX() * this->mouseSensitivity, this->input->getMouseOffsetY() * this->mouseSensitivity);
}

CameraController::CameraController(Camera *camera, HardwareInput *input, float speed, float mouseSensitivity)
    : camera(camera), input(input), speed(speed), mouseSensitivity(mouseSensitivity)
{
}

void CameraController::setSpeed(float newSpeed)
{
    this->speed = newSpeed;
}
void CameraController::setMouseSensitivity(float newMouseSensitivity)
{
    this->mouseSensitivity = newMouseSensitivity;
}

void CameraController::Update()
{
    this->handleRotation();
    this->handleMovement();
}