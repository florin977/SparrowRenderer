#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include <glm/glm.hpp>
#include "Shader.hpp"
#include "Window.hpp"
#include "Buffers/VertexBuffer.hpp"
#include "Buffers/VertexArray.hpp"
#include "Buffers/ElementBuffer.hpp"
#include "Buffers/UniformBuffer.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Model.hpp"
#include "Entity.hpp"
#include "Camera.hpp"

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280

// Start mouse in the center of the screen
float lastX = WINDOW_WIDTH / 2.0;
float lastY = WINDOW_HEIGHT / 2.0;
bool firstMouse = true;
Camera *camera = nullptr;

void mouse_callback(GLFWwindow *window, double xPosIn, double yPosIn)
{
    float xPos = static_cast<float>(xPosIn);
    float yPos = static_cast<float>(yPosIn);

    // Prevents a camera jump when the mouse first enters the window
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos; // Reversed: Screen Y goes from top to bottom, but 3D Y goes from bottom to top

    lastX = xPos;
    lastY = yPos;

    float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    if (camera != nullptr)
    {
        camera->rotate(xOffset, yOffset);
    }
}

void processInput(Window &window, Camera &camera)
{
    if (window.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        window.setShouldClose(true);
    }

    if (window.isKeyPressed(GLFW_KEY_W))
    {
        camera.moveForward(0.2);
    }
    if (window.isKeyPressed(GLFW_KEY_S))
    {
        camera.moveForward(-0.2);
    }

    if (window.isKeyPressed(GLFW_KEY_A))
    {
        camera.moveRight(-0.2);
    }
    if (window.isKeyPressed(GLFW_KEY_D))
    {
        camera.moveRight(0.2);
    }

    if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        camera.moveUp(0.2);
    }
    if (window.isKeyPressed(GLFW_KEY_LEFT_CONTROL))
    {
        camera.moveUp(-0.2);
    }
}

// Call shader.use() BEFORE drawing

int main(void)
{
    Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sparrow Renderer");
    {
        // Hide cursor and lock it to the screen
        glfwSetInputMode(mainWindow.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSetCursorPosCallback(mainWindow.getGLFWwindow(), mouse_callback);

        Camera mainCamera;
        camera = &mainCamera;

        Shader shader("../shaders/vertexShader.vert", "../shaders/fragmentShader.frag");
        Model model("../Assets/LearnOpenGL/scene.gltf");
        Entity cube(&model);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        /* Loop until the user closes the window */
        while (!mainWindow.shouldClose())
        {
            processInput(mainWindow, mainCamera);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            mainCamera.Update();

            shader.use();
            cube.Draw(shader);

            /* Poll for and process events */
            mainWindow.pollEvents();

            /* Swap front and back buffers */
            mainWindow.swapBuffers();
        }
    }

    return 0;
}