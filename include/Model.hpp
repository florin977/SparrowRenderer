#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Texture.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

class Model
{
private:
    std::unordered_map<std::string, Texture> loadedTextures;
    std::vector<std::unique_ptr<Material>> loadedMaterials;
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

public:
    Model(const std::string &path);
    Texture *getTexture(const std::string &fullPath, const unsigned int textureType);
    void Draw(Shader &shader);
};