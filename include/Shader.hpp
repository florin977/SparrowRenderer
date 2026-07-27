#pragma once

#include <string>

class Shader
{
private:
    unsigned int programId;
public:
    Shader();

    void attachShader(const unsigned int shaderType, const std::string &path);

    void link();

    void use() const;

    ~Shader();
};
