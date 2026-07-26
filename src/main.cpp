#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

#define WINDOW_HEIGHT 960
#define WINDOW_WIDTH 1280

std::vector<float> vertices(9);

void error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error [" << error << "]: " << description << std::endl;
}

void framebuffer_resize_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } 
}

std::optional<std::string> readShaderCode(const std::string& path) {
    std::ifstream file(path, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << path << std::endl;
        return std::nullopt;
    }

    size_t fileSize = (size_t)file.tellg();

    std::string buffer(fileSize, ' ');

    file.seekg(0);

    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
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

    glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if (!glfwInit()) {
        std::cerr << "FATAL: Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello, World!", NULL, NULL);
    if (!window)
    {
        std::cerr << "FATAL: Failed to create GLFW window! (Check if your driver supports OpenGL 4.6 Core)" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    if (version == 0) {
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


    std::optional<std::string> vertexShaderSrc = readShaderCode("../shaders/vertexShader.vert");
    std::optional<std::string> fragmentShaderSrc = readShaderCode("../shaders/fragmentShader.frag");

    if (!vertexShaderSrc.has_value()) {
        std::cerr << "No vertex shader provided\n";
        return -1;
    }

    if (!fragmentShaderSrc.has_value()) {
        std::cerr << "No fragment shader provided\n";

    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *vShaderCode = vertexShaderSrc.value().c_str();
    const char *fShaderCode = fragmentShaderSrc.value().c_str();

    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);

    int  success;
    char infoLog[512];

    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        
        std::cerr << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
     
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Poll for and process events */
        glfwPollEvents();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}