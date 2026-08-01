#include "Model.hpp"

Texture *Model::getTexture(const std::string &fullPath, const unsigned int textureType)
{
    auto it = loadedTextures.find(fullPath);

    if (it == loadedTextures.end())
    {
        loadedTextures.try_emplace(fullPath, fullPath, textureType, GL_TEXTURE_2D);
        return &loadedTextures[fullPath];
    }

    return &(it->second);
}

void Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Texture *diffusePtr = nullptr;
    Texture *specularPtr = nullptr;
    Texture *normalPtr = nullptr;

    // Process vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        glm::vec3 pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        glm::vec2 uv;
        if (mesh->mTextureCoords[0])
        {
            uv = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }
        else
        {
            uv = glm::vec2(0.0, 0.0);
        }
        glm::vec3 normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        Vertex vertex(pos, uv, normal);
        vertices.push_back(vertex);
    }

    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process material
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
        aiString str;

        unsigned int diffuseCount = mat->GetTextureCount(aiTextureType_DIFFUSE);
        unsigned int specularCount = mat->GetTextureCount(aiTextureType_SPECULAR);
        unsigned int normalCount = mat->GetTextureCount(aiTextureType_NORMALS);

        if (diffuseCount > 0)
        {

            mat->GetTexture(aiTextureType_DIFFUSE, 0, &str);

            if (diffuseCount > 1)
            {
                std::cerr << "More than one diffuse texture for model: " << this->directory << std::endl;
            }

            const std::string fullPath = this->directory + "/" + str.C_Str();
            diffusePtr = this->getTexture(fullPath, TEXTURE_DIFFUSE);
        }

        if (specularCount > 0)
        {
            mat->GetTexture(aiTextureType_SPECULAR, 0, &str);

            if (specularCount > 1)
            {
                std::cerr << "More than one specular texture for model: " << this->directory << std::endl;
            }

            const std::string fullPath = this->directory + "/" + str.C_Str();
            specularPtr = this->getTexture(fullPath, TEXTURE_SPECULAR);
        }

        if (normalCount > 0)
        {
            mat->GetTexture(aiTextureType_NORMALS, 0, &str);

            if (normalCount > 1)
            {
                std::cerr << "More than one specular texture for model: " << this->directory << std::endl;
            }

            const std::string fullPath = this->directory + "/" + str.C_Str();
            normalPtr = this->getTexture(fullPath, TEXTURE_NORMAL);
        }
    }

    std::unique_ptr<Material> material = std::make_unique<Material>(diffusePtr, specularPtr, normalPtr);
    Material *rawMaterialPtr = material.get();

    this->loadedMaterials.push_back(std::move(material));

    this->meshes.emplace_back(vertices, indices, rawMaterialPtr);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // Process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }
    // Then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void Model::loadModel(const std::string &path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Error reading model file: " << import.GetErrorString() << std::endl;
    }

    this->directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

Model::Model(const std::string &path)
{
    loadModel(path);
}

void Model::Draw(Shader &shader)
{
    auto it = this->meshes.begin();

    while (it != this->meshes.end())
    {
        it->Draw(shader);
        it++;
    }
}