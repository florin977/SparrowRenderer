#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// TODO: Maybe add a uniform cache in the future

class Shader
{
private:
    unsigned int programId;

public:
    Shader(const std::string &vertexShaderPath = "", const std::string &fragmetShaderPath = "");

    void attachShader(const unsigned int shaderType, const std::string &path);

    // WARNING: Always use the shader before changing the values
    void setBool(const std::string &uniformName, bool value);
    void setInt(const std::string &uniformName, int value);
    void setFloat(const std::string &uniformName, float value);
    void setUnsignedInt(const std::string &uniformName, unsigned int value);
    void setMatrix4(const unsigned int layoutLocation, const glm::mat4 matrix);
    void setVector3(const unsigned int layoutLocation, const glm::vec3 vector);
    
    void link();

    void use() const;

    ~Shader();
};
