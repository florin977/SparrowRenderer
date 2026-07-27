#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
private:
    GLFWwindow *window;
    int width = 1280;
    int height = 960;

public:
    Window(int width, int height, const std::string& windowName);

    ~Window();

    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;


    int getWidth();
    int getHeight();
    GLFWwindow *getGLFWwindow() const;

    void setWidth(int width);
    void setHeight(int height);

    bool isKeyPressed(int key) const;
    void setShouldClose(int value);
};