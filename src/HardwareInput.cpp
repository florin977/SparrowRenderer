#include "HardwareInput.hpp"
#include <iostream>
#include <unordered_map>

std::unordered_map<GLFWwindow *, HardwareInput *> HardwareInput::instances;

void HardwareInput::updateMouse()
{
    double posX, posY;
    glfwGetCursorPos(this->window->getGLFWwindow(), &posX, &posY);

    // Prevent a camera snap
    if (this->firstMouseMovement)
    {
        this->mouse_currentX = static_cast<float>(posX);
        this->mouse_currentY = static_cast<float>(posY);
        this->firstMouseMovement = false;
    }

    this->mouse_lastX = this->mouse_currentX;
    this->mouse_lastY = this->mouse_currentY;

    this->mouse_currentX = static_cast<float>(posX);
    this->mouse_currentY = static_cast<float>(posY);
}

void HardwareInput::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    auto it = instances.find(window);

    if (it != instances.end() && key >= 0 && key <= GLFW_KEY_LAST)
    {
        HardwareInput *input = it->second;
        if (action == GLFW_PRESS)
        {
            input->currentFrame_pressedKeys.set(key, true);
        }
        else if (action == GLFW_RELEASE)
        {
            input->currentFrame_pressedKeys.set(key, false);
        }
    }
}

HardwareInput::HardwareInput(Window *window)
    : window(window), firstMouseMovement(true)
{
    if (window == nullptr)
    {
        std::cerr << "Invalid window: nullptr exception" << std::endl;
        return;
    }

    instances[this->window->getGLFWwindow()] = this;

    glfwSetKeyCallback(this->window->getGLFWwindow(), keyCallback);

    this->mouse_lastX = this->window->getWidth() / 2.0;
    this->mouse_lastY = this->window->getHeight() / 2.0;

    this->mouse_currentX = this->mouse_lastX;
    this->mouse_currentY = this->mouse_lastY;
}

HardwareInput::~HardwareInput()
{
    if (this->window)
    {
        instances.erase(this->window->getGLFWwindow());
    }
}

bool HardwareInput::keyPressed(const int key) const
{
    if (key < 0 || key >= GLFW_KEY_LAST)
    {
        return false;
    }

    return currentFrame_pressedKeys.test(key);
}
bool HardwareInput::keyJustPressed(const int key) const
{

    if (key < 0 || key >= GLFW_KEY_LAST)
    {
        return false;
    }

    return currentFrame_pressedKeys.test(key) && !lastFrame_pressedKeys.test(key);
}
bool HardwareInput::keyJustReleased(const int key) const
{

    if (key < 0 || key >= GLFW_KEY_LAST)
    {
        return false;
    }

    return !currentFrame_pressedKeys.test(key) && lastFrame_pressedKeys.test(key);
}

void HardwareInput::poll()
{

    lastFrame_pressedKeys = currentFrame_pressedKeys;

    if (this->keyPressed(GLFW_KEY_ESCAPE))
    {
        this->window->setShouldClose(true);
    }

    this->updateMouse();
}

float HardwareInput::getMouseOffsetX() const
{
    return (this->mouse_currentX - this->mouse_lastX);
}
float HardwareInput::getMouseOffsetY() const
{
    return (this->mouse_lastY - this->mouse_currentY);
}