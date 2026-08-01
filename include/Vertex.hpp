#pragma once
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 uv;
    glm::vec3 normal;

    Vertex() = default;
    Vertex(glm::vec3 pos, glm::vec2 uv, glm::vec3 normal) : pos(pos), uv(uv), normal(normal) {}
};