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

std::vector<float> vertices(9 * 100000);


void processInput(Window &window)
{
    if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
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

    vertices[6] = 0.0;
    vertices[7] = 0.5;
    vertices[8] = 0.0;

    for (int i = 1; i < 100000; i++)
    {
        float v00 = 2 * (((float)rand() / (RAND_MAX)) - 0.5);
        float v01 = 2 * (((float)rand() / (RAND_MAX)) - 0.5);
        float v02 = 2 * (((float)rand() / (RAND_MAX)) - 0.5);

        float v10 = 2 * (((float)rand() / (RAND_MAX)) - 0.5);
        float v11 = 2 * (((float)rand() / (RAND_MAX)) - 0.5);
        float v12 = 2 * (((float)rand() / (RAND_MAX)) - 0.5);

        float v20 = 2 * (((float)rand() / (RAND_MAX)) - 0.5);
        float v21 = 2 * (((float)rand() / (RAND_MAX)) - 0.5);
        float v22 = 2 * (((float)rand() / (RAND_MAX)) - 0.5);

        vertices[9 * i] = v00;
        vertices[9 * i + 1] = v01;
        vertices[9 * i + 2] = v02;

        vertices[9 * i + 3] = v10;
        vertices[9 * i + 4] = v11;
        vertices[9 * i + 5] = v12;

        vertices[9 * i + 6] = v20;
        vertices[9 * i + 7] = v21;
        vertices[9 * i + 8] = v22;
    }

    Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sparrow Renderer");

    {
        VertexArray VAO;
        VAO.bind();

        VertexBuffer VBO(vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
        VBO.bind();

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
            glDrawArrays(GL_TRIANGLES, 0, 3 * 100);

            /* Poll for and process events */
            mainWindow.pollEvents();

            /* Swap front and back buffers */
            mainWindow.swapBuffers();
        }
    }

    return 0;
}