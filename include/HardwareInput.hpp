#pragma once

#include "Window.hpp"
#include <bitset>
#include <unordered_map>

class HardwareInput
{
private:
    Window *window;
    float mouse_lastX, mouse_lastY;
    float mouse_currentX, mouse_currentY;
    bool firstMouseMovement;
    std::bitset<GLFW_KEY_LAST + 1> lastFrame_pressedKeys;
    std::bitset<GLFW_KEY_LAST + 1> currentFrame_pressedKeys;
    static std::unordered_map<GLFWwindow *, HardwareInput *> instances; // needed for the keyCallback to work

    void updateMouse();
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
    HardwareInput(Window *window);
    ~HardwareInput();
    bool keyPressed(const int key) const;
    bool keyJustPressed(const int key) const;
    bool keyJustReleased(const int key) const;

    void poll();

    float getMouseOffsetX() const;
    float getMouseOffsetY() const;
};