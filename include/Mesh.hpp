#pragma once
#include <vector>
#include "Vertex.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "Buffers/VertexArray.hpp"
#include "Buffers/VertexBuffer.hpp"
#include "Buffers/ElementBuffer.hpp"

class Mesh
{
private:
    VertexArray VAO;
    VertexBuffer VBO;
    ElementBuffer EBO;
    void setupMesh();

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material *material;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material *material);
    ~Mesh();

    void Draw(const Shader &shader);
};