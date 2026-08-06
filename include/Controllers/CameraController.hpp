#pragma once

#include "Camera.hpp"
#include "Entity.hpp"
#include "HardwareInput.hpp"

class CameraController
{
private:
    Camera *camera;
    HardwareInput *input;
    float speed;
    float mouseSensitivity;

    void handleMovement();
    void handleRotation();

public:
    CameraController(Camera *camera, HardwareInput *input, float speed, float mouseSensitivity);
    void setSpeed(float newSpeed);
    void setMouseSensitivity(float newMouseSensitivity);
    void Update();
};