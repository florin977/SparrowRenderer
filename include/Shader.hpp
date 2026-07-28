#pragma once

#include <string>

// TODO: Maybe add a uniform cache in the future

class Shader
{
private:
    unsigned int programId;

public:
    Shader();

    void attachShader(const unsigned int shaderType, const std::string &path);

    // WARNING: Always use the shader before changing the values
    void setBool(const std::string &uniformName, bool value);
    void setInt(const std::string &uniformName, int value);
    void setFloat(const std::string &uniformName, float value);
    void setUnsignedInt(const std::string &uniformName, unsigned int value);

    void link();

    void use() const;

    ~Shader();
};
