#pragma once
#include <string>

enum TextureType
{
    TEXTURE_ALBEDO,
    TEXTURE_NORMAL,
    TEXTURE_DIFFUSE,
    TEXTURE_SPECULAR,
};

class Texture
{
private:
    unsigned int textureId, textureType, textureTarget;
    int width, height, nrChannels;

public:
    Texture(const std::string &path, const unsigned int textureType, const unsigned int textureTarget);

    void bind(const unsigned int textureUnit) const;
    void unbind(const unsigned int textureUnit) const;

    ~Texture();
};