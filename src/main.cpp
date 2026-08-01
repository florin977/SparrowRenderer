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
#include "Texture.hpp"
#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Model.hpp"

#define WINDOW_HEIGHT 960
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

int main(void)
{
    // bottom-left
    vertices[0].pos = glm::vec3(-0.5, -0.5, 0.0);
    vertices[0].uv = glm::vec2(0.0, 0.0);

    // bottom-right
    vertices[1].pos = glm::vec3(0.5, -0.5, 0.0);
    vertices[1].uv = glm::vec2(1.0, 0.0);

    // top-left
    vertices[2].pos = glm::vec3(-0.5, 0.5, 0.0);
    vertices[2].uv = glm::vec2(0.0, 1.0);

    // top-right
    vertices[3].pos = glm::vec3(0.5, 0.5, 0.0);
    vertices[3].uv = glm::vec2(1.0, 1.0);

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 1;
    indices[4] = 2;
    indices[5] = 3;

    Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sparrow Renderer");

    Model backpack("../Assets/LearnOpenGL/scene.gltf");
    Texture sparrowTexture("../Textures/sparrow.jpg", TEXTURE_DIFFUSE, GL_TEXTURE_2D);

    {
        Material sparrowImage(&sparrowTexture);
        
        Mesh cube(vertices, indices, &sparrowImage);   

        Shader shader("../shaders/vertexShader.vert", "../shaders/fragmentShader.frag");

        /* Loop until the user closes the window */
        while (!mainWindow.shouldClose())
        {
            processInput(mainWindow);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            //cube.Draw(shader);
            backpack.Draw(shader);

            /* Poll for and process events */
            mainWindow.pollEvents();

            /* Swap front and back buffers */
            mainWindow.swapBuffers();
        }
    }

    return 0;
}