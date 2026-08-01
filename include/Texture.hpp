#pragma once
#include <string>

enum TextureType
{
    TEXTURE_DIFFUSE,
    TEXTURE_SPECULAR,
    TEXTURE_NORMAL,
};

class Texture
{
private:
    unsigned int textureId, textureType, textureTarget;
    int width, height, nrChannels;
    std::string path;

public:
    Texture();
    Texture(const std::string &path, const unsigned int textureType, const unsigned int textureTarget);

    void bind(const unsigned int textureUnit) const;
    void unbind(const unsigned int textureUnit) const;

    ~Texture();
};