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
#include "DirectionalLight.hpp"
#include "UI.hpp"
#include "HardwareInput.hpp"

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280

void processInput(HardwareInput &input, Camera &camera)
{
    float mouseSensitivity = 0.5;
    camera.rotate(input.getMouseOffsetX() * mouseSensitivity , input.getMouseOffsetY() * mouseSensitivity);

    float speed = 0.5;

    if (input.keyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        speed = 3.0;
    }
    else
    {
        speed = 0.5;
    }

    if (input.keyPressed(GLFW_KEY_W))
    {
        camera.moveForward(speed);
    }
    if (input.keyPressed(GLFW_KEY_S))
    {
        camera.moveForward(-speed);
    }

    if (input.keyPressed(GLFW_KEY_A))
    {
        camera.moveRight(-speed);
    }
    if (input.keyPressed(GLFW_KEY_D))
    {
        camera.moveRight(speed);
    }

    if (input.keyPressed(GLFW_KEY_SPACE))
    {
        camera.moveUp(speed);
    }
    if (input.keyPressed(GLFW_KEY_LEFT_CONTROL))
    {
        camera.moveUp(-speed);
    }
}

// Call shader.use() BEFORE drawing

int main(void)
{
    Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sparrow Renderer");
    {
        Camera mainCamera;
        mainCamera.setFarPlane(2000.0);
        HardwareInput input(&mainWindow);

        UI ui(&mainWindow, &mainCamera);
        {
            // Hide cursor and lock it to the screen
            glfwSetInputMode(mainWindow.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_CAPTURED);

            Shader shader("../shaders/vertexShader.vert", "../shaders/fragmentShader.frag");
            Shader lightShader("../shaders/vertexShader.vert", "../shaders/lightFragmentShader.frag");

            Model model("../Assets/LearnOpenGL/scene.gltf");
            // Model model("../Assets/Duck/Duck.gltf");
            Model lightModel("../Assets/Box/BoxTextured.gltf");
            Entity cube(&model);
            Entity lightEntity(&lightModel);
            lightEntity.setScale(glm::vec3(100.0, 100.0, 100.0));
            DirectionalLight light(glm::vec4(1.0, 2.0, 250.0, 1.0), glm::vec4(1.0), &lightEntity);

            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);

            /* Loop until the user closes the window */
            while (!mainWindow.shouldClose())
            {
                /* Poll for and process events */
                mainWindow.pollEvents();

                input.poll();
                processInput(input, mainCamera);

                ui.beginFrame();

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                mainCamera.Update();

                shader.use();
                cube.Draw(shader);

                lightShader.use();
                light.Draw(lightShader);

                ui.Draw();

                /* Swap front and back buffers */
                mainWindow.swapBuffers();
            }
        }
    }
    return 0;
}