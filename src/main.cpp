#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include "Shader.hpp"
#include "Window.hpp"
#include "Buffers/VertexBuffer.hpp"
#include "Buffers/VertexArray.hpp"
#include "Buffers/ElementBuffer.hpp"
#include "Texture.hpp"

#define WINDOW_HEIGHT 960
#define WINDOW_WIDTH 1280

std::vector<float> vertices(20);
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
    vertices[0] = -0.5;
    vertices[1] = -0.5;
    vertices[2] = 0.0;
    // UV coord
    vertices[3] = 0.0;
    vertices[4] = 0.0;

    // bottom-right
    vertices[5] = 0.5;
    vertices[6] = -0.5;
    vertices[7] = 0.0;
    // UV coord
    vertices[8] = 1.0;
    vertices[9] = 0.0;

    // top-left
    vertices[10] = -0.5;
    vertices[11] = 0.5;
    vertices[12] = 0.0;
    // UV coord
    vertices[13] = 0.0;
    vertices[14] = 1.0;

    // top-right
    vertices[15] = 0.5;
    vertices[16] = 0.5;
    vertices[17] = 0.0;
    // UV coord
    vertices[18] = 1.0;
    vertices[19] = 1.0;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 1;
    indices[4] = 2;
    indices[5] = 3;

    Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sparrow Renderer");

    Texture sparrowTexture("../Textures/sparrow.jpg", GL_TEXTURE_2D);

    {
        VertexArray VAO;
        VAO.bind();

        VertexBuffer VBO(vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
        VBO.bind();

        ElementBuffer EBO(indices.data(), indices.size());
        EBO.bind();

        // Vertex position
        VAO.linkAttribute(VBO, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        // Vertex UV coordinate
        VAO.linkAttribute(VBO, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
        Shader shader;

        shader.attachShader(GL_VERTEX_SHADER, "../shaders/vertexShader.vert");
        shader.attachShader(GL_FRAGMENT_SHADER, "../shaders/fragmentShader.frag");
        shader.link();
        shader.use();

        VAO.bind();
        sparrowTexture.bind(0);
        shader.setInt("sparrowTexture", 0);

        /* Loop until the user closes the window */
        while (!mainWindow.shouldClose())
        {
            processInput(mainWindow);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            /* Poll for and process events */
            mainWindow.pollEvents();

            /* Swap front and back buffers */
            mainWindow.swapBuffers();
        }
    }

    return 0;
}