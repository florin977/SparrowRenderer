#pragma once

#include <string>

class Shader
{
public:
    unsigned int programId;
    
    Shader();

    void attachShader(const unsigned int shaderType, const std::string &path);

    void link();

    void use() const;

    ~Shader();
};
