#include "Shader.hpp"
#include <glad/glad.h>
#include <optional>
#include <fstream>
#include <iostream>

static std::optional<std::string> readShaderFile(const std::string &path)
{
    std::ifstream file(path, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
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

static std::optional<unsigned int> compileShader(const unsigned int shaderType, const std::string &path)
{
    int success;
    char infoLog[512];

    std::optional<std::string> shaderSrc = readShaderFile(path);

    if (!shaderSrc.has_value())
    {
        std::cerr << "Shader not provided: " << path << '\n';
        return std::nullopt;
    }

    unsigned int shader = glCreateShader(shaderType);
    const char *shaderCode = shaderSrc.value().c_str();

    glShaderSource(shader, 1, &shaderCode, NULL);

    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED for file: " << path << "\n"
                  << infoLog << std::endl;
        return std::nullopt;
    }

    return shader;
}

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmetShaderPath)
{
    this->programId = glCreateProgram();

    if (vertexShaderPath != "")
        this->attachShader(GL_VERTEX_SHADER, vertexShaderPath);
    if (fragmetShaderPath != "")
        this->attachShader(GL_FRAGMENT_SHADER, fragmetShaderPath);

    this->link();
}

void Shader::attachShader(const unsigned int shaderType, const std::string &path)
{
    std::optional<unsigned int> shader = compileShader(shaderType, path);

    if (shader.has_value())
    {
        glAttachShader(programId, shader.value());

        glDeleteShader(shader.value());
    }
}

void Shader::setBool(const std::string &uniformName, bool value)
{
    glProgramUniform1i(programId, glGetUniformLocation(programId, uniformName.c_str()), value);
}
void Shader::setInt(const std::string &uniformName, int value)
{
    glProgramUniform1i(programId, glGetUniformLocation(programId, uniformName.c_str()), value);
}
void Shader::setFloat(const std::string &uniformName, float value)
{
    glProgramUniform1f(programId, glGetUniformLocation(programId, uniformName.c_str()), value);
}
void Shader::setUnsignedInt(const std::string &uniformName, unsigned int value)
{
    glProgramUniform1ui(programId, glGetUniformLocation(programId, uniformName.c_str()), value);
}

void Shader::link()
{
    int success;
    char infoLog[512];

    glLinkProgram(programId);
    glGetProgramiv(programId, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
}

void Shader::use() const
{
    glUseProgram(programId);
}

Shader::~Shader()
{
    glDeleteProgram(programId);
}