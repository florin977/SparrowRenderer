#include "Texture.hpp"
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>

Texture::Texture() : path(""), textureType(0), textureTarget(0), textureId(0), width(0), height(0), nrChannels(0)
{}

Texture::Texture(const std::string &path, const unsigned int textureType, const unsigned int textureTarget)
: path(path), textureType(textureType), textureTarget(textureTarget)
{
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glGenTextures(1, &textureId);
        glBindTexture(this->textureTarget, textureId);

        unsigned int format;
        switch (nrChannels)
        {
        case 1:
            format = GL_RED;
            break;
        case 2:
            format = GL_RG;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            format = GL_RGB;
            break;
        }
        // In case image's width is not a multiple of 4, the texture appears diagonally skewed. This prevents it.
        // WARNING: It is slower to upload to the GPU.
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        if (this->textureTarget == GL_TEXTURE_2D)
        {
            glTexImage2D(this->textureTarget, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(this->textureTarget);

            // Default warping and filtering parameters
            glTexParameteri(this->textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(this->textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(this->textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(this->textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            std::cerr << "Unsupported texture target: " << this->textureTarget << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to load image data for image: " << path << std::endl;
    }

    stbi_image_free(data);
}

void Texture::bind(const unsigned int textureUnit) const
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(textureTarget, textureId);
}
void Texture::unbind(const unsigned int textureUnit) const
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(textureTarget, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureId);
}