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

#define WINDOW_HEIGHT 960
#define WINDOW_WIDTH 1280

std::vector<float> vertices(12);
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
    vertices[0] = -0.5;
    vertices[1] = -0.5;
    vertices[2] = 0.0;

    vertices[3] = 0.5;
    vertices[4] = -0.5;
    vertices[5] = 0.0;

    vertices[6] = -0.5;
    vertices[7] = 0.5;
    vertices[8] = 0.0;

    vertices[9] = 0.5;
    vertices[10] = 0.5;
    vertices[11] = 0.0;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 1;
    indices[4] = 2;
    indices[5] = 3;

    Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sparrow Renderer");

    {
        VertexArray VAO;
        VAO.bind();

        VertexBuffer VBO(vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
        VBO.bind();

        ElementBuffer EBO(indices.data(), indices.size());
        EBO.bind();

        VAO.linkAttribute(VBO, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

        Shader shader;

        shader.attachShader(GL_VERTEX_SHADER, "../shaders/vertexShader.vert");
        shader.attachShader(GL_FRAGMENT_SHADER, "../shaders/fragmentShader.frag");
        shader.link();
        shader.use();

        VAO.bind();

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