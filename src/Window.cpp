#include "Window.hpp"
#include <glad/glad.h>
#include <iostream>

static void error_callback(int error, const char *description)
{
    std::cerr << "GLFW Error [" << error << "]: " << description << std::endl;
}

static void framebuffer_resize_callback(GLFWwindow *glfwWindow, int width, int height)
{
    Window *myWindow = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));

    myWindow->setWidth(width);
    myWindow->setHeight(height);

    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const std::string &windowName)
    : width(width), height(height)
{
    glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cerr << "FATAL: Failed to initialize GLFW!" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
    if (!window)
    {
        std::cerr << "FATAL: Failed to create GLFW window! (Check if your driver supports OpenGL 4.6 Core)" << std::endl;
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    if (version == 0)
    {
        std::cerr << "FATAL: Failed to initialize GLAD headers! (Profile mismatch between GLAD and GLFW)" << std::endl;
        glfwTerminate();
        return;
    }
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(window);
}

void Window::pollEvents() const
{
    glfwPollEvents();
}

int Window::getWidth()
{
    return width;
}

int Window::getHeight()
{
    return height;
}

GLFWwindow *Window::getGLFWwindow() const
{
    return this->window;
}

void Window::setWidth(int width)
{
    this->width = width;
}
void Window::setHeight(int height)
{
    this->height = height;
}

bool Window::isKeyPressed(int key) const
{
    return (glfwGetKey(window, key) == GLFW_PRESS);
}

void Window::setShouldClose(int value)
{
    glfwSetWindowShouldClose(window, value);
}
