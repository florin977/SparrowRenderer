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
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material *material;
    VertexArray VAO;
    VertexBuffer VBO;
    ElementBuffer EBO;

    void setupMesh();

public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material *material);
    void Draw(Shader &shader);
};