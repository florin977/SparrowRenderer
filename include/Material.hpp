#pragma once
#include <vector>
#include "Texture.hpp"

class Material
{
private:
    Texture *diffuseMap;
    Texture *specularMap;
    Texture *normalMap;

public:
    Material(Texture *diffuseMap = nullptr, Texture *specularMap = nullptr, Texture *normalMap = nullptr);

    void bind() const
    {
        if (diffuseMap)
            diffuseMap->bind(0);
        if (specularMap)
            specularMap->bind(1);
        if (normalMap)
            normalMap->bind(2);
    }
};