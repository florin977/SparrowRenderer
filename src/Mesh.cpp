#include "Mesh.hpp"

void Mesh::setupMesh()
{
    this->VAO = VertexArray();
    this->VBO = VertexBuffer(this->vertices.size() * sizeof(this->vertices[0]), this->vertices.data(), GL_STATIC_DRAW);
    this->EBO = ElementBuffer(this->indices.data(), indices.size());

    this->VAO.bind();
    this->VBO.bind();
    this->EBO.bind();

    VAO.linkAttribute(this->VBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
    VAO.linkAttribute(this->VBO, 1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
    VAO.linkAttribute(this->VBO, 2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material *material)
    : vertices(std::move(vertices)), indices(std::move(indices)), material(material)
{
    setupMesh();
}

void Mesh::Draw(const Shader &shader) {

}