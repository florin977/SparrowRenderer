#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include "Shader.hpp"

#define WINDOW_HEIGHT 960
#define WINDOW_WIDTH 1280

std::vector<float> vertices(9 * 100000);

void error_callback(int error, const char *description)
{
    std::cerr << "GLFW Error [" << error << "]: " << description << std::endl;
}

void framebuffer_resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
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

    glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cerr << "FATAL: Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello, World!", NULL, NULL);
    if (!window)
    {
        std::cerr << "FATAL: Failed to create GLFW window! (Check if your driver supports OpenGL 4.6 Core)" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    {
        glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

        int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        if (version == 0)
        {
            std::cerr << "FATAL: Failed to initialize GLAD headers! (Profile mismatch between GLAD and GLFW)" << std::endl;
            glfwTerminate();
            return -1;
        }

        unsigned int VAO = 0;
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);

        unsigned int VBO = 0;
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        Shader shader;

        shader.attachShader(GL_VERTEX_SHADER, "../shaders/vertexShader.vert");
        shader.attachShader(GL_FRAGMENT_SHADER, "../shaders/fragmentShader.frag");
        shader.link();
        shader.use();

        glBindVertexArray(VAO);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawArrays(GL_TRIANGLES, 0, 3 * 100);

            /* Poll for and process events */
            glfwPollEvents();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    glfwTerminate();

    return 0;
}