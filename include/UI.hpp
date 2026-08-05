#pragma once

#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Window.hpp"
#include "Camera.hpp"

class UI
{
private:
    const Window *window;
    const Camera *camera;
public:
    UI(const Window *window = nullptr, const Camera *camera = nullptr);
    ~UI();

    void beginFrame();
    void Draw();
};