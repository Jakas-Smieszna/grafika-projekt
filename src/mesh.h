#ifndef MESH_CLASS_H
#define MESH_CLASS_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "EBO.h"
#include "VBO.h"
#include "VAO.h"
#include "glm/fwd.hpp"
#include "shader.h"
#include "vertex.h"

#define Mesh _mesh

class _mesh {
    public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    _mesh(
        std::vector<Vertex> vertices,
        std::vector<GLuint> indices);
    void Draw(Shader &shader);
    private:
    VAO vao; 
    VBO vbo; 
    EBO ebo;
    void initMesh();
};

Mesh getTestMesh();

#endif // MESH_CLASS_H