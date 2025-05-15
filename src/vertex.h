#ifndef VERTEX_STRUCT_H
#define VERTEX_STRUCT_H
#include <glm/glm.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec2 TexCoords;
    glm::vec3 Normal;
};

#endif