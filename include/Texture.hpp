#pragma once
#include <string>

class Texture
{
private:
    unsigned int textureId, textureType;
    int width, height, nrChannels;
public:
    Texture(const std::string &path, const unsigned int textureType);

    void bind(const unsigned int textureUnit) const;
    void unbind(const unsigned int textureUnit) const;

    ~Texture();
};