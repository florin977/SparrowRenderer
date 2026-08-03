#pragma once
#include <vector>
#include <list>
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

struct ModelNode
{
    std::string name;
    glm::mat4 localTransform;
    unsigned int meshIndex;
};

class Model
{
private:
    std::unordered_map<std::string, Texture> loadedTextures;
    std::vector<std::unique_ptr<Material>> loadedMaterials;
    std::vector<Mesh> meshes;
    std::vector<ModelNode> nodes;
    std::string directory;

    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene, const glm::mat4 &parentTransform);
    unsigned int processMesh(aiMesh *mesh, const aiScene *scene);

public:
    Model(const std::string &path);
    Texture *getTexture(const std::string &fullPath, const unsigned int textureType);
    void Draw(Shader &shader, const glm::mat4 &modelMatrix);
};