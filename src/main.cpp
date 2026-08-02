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

std::vector<Vertex> vertices(4);
std::vector<unsigned int> indices(6);

void processInput(Window &window)
{
    if (window.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        window.setShouldClose(true);
    }
}

// Call shader.use() BEFORE drawing

int main(void)
{
    Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sparrow Renderer");
    {
        Camera mainCamera(glm::vec3(0.0, 0.5, 5.0));
        Shader shader("../shaders/vertexShader.vert", "../shaders/fragmentShader.frag");
        Model model("../Assets/Box/BoxTextured.gltf");
        Entity cube(&model);

        glEnable(GL_DEPTH_TEST);

        /* Loop until the user closes the window */
        while (!mainWindow.shouldClose())
        {
            processInput(mainWindow);

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