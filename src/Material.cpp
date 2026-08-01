#include "Material.hpp"

Material::Material(Texture *diffuseMap, Texture *specularMap, Texture *normalMap)
    : diffuseMap(diffuseMap), specularMap(specularMap), normalMap(normalMap) {}