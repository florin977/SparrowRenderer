#pragma once
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;

    Vertex() = default;
    Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 uv) : pos(pos), normal(normal), uv(uv) {}
};