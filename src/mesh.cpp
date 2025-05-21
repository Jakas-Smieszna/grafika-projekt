#include "mesh.h"
#include "shader.h"
#include "vertex.h"
#include <vector>
#include <iostream>

_mesh::_mesh() {
    initMesh();
}

_mesh::_mesh(
        std::vector<Vertex> vertices,
        std::vector<GLuint> indices
    ) {
        this->vertices = vertices;
        this->indices = indices;
        initMesh();
    }

void _mesh::initMesh() {
    vao = VAO();
    vao.Bind();

    vbo = VBO(vertices, vertices.size() * sizeof(Vertex));
    ebo = EBO(indices, indices.size() * sizeof(GLuint));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    vao.LinkAttrib(vbo, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
}

void _mesh::Draw(Shader &shader) {
    shader.Activate();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
}

// TODO: template?
// template<typename VertType>
std::vector<Vertex> vertexVectorFromVertexArray(GLfloat* vertexArray, size_t elems) {
    std::vector<Vertex> vertexVect;
    
    for(int i = 0; i < elems; i+=11) {
        vertexVect.push_back(Vertex{
            glm::vec3{vertexArray[i], vertexArray[i+1], vertexArray[i+2]},
            glm::vec3{vertexArray[i+3], vertexArray[i+4], vertexArray[i+5]},
            glm::vec2{vertexArray[i+6], vertexArray[i+7]},
            glm::vec3{vertexArray[i+8], vertexArray[i+9], vertexArray[i+10]}
        });
    }
    return vertexVect;
}

Mesh getTestMesh() {
    GLfloat v[] = {
   -0.5f, 1.5f,  0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f,								0.0f, -1.0f, 0.0f,
   -0.5f, 1.5f, -0.5f,0.0f, 1.0f, 1.0f,0.0f, 3.0f,	0.0f,   -1.0f, 0.0f,
	0.5f, 1.5f, -0.5f,1.0f, 1.0f, 0.0f,3.0f, 3.0f,	0.0f,   -1.0f, 0.0f,
	0.5f, 1.5f,  0.5f,0.0f, 1.0f, 1.0f,3.0f, 0.0f,	0.0f,   -1.0f, 0.0f
    };

    volatile size_t vsize = sizeof(v) / sizeof(v[0]); 
    std::cout << vsize;

    std::vector<GLuint> indexVect = {
        0, 1, 3,
        1, 3, 2
    };
    Mesh r = Mesh(vertexVectorFromVertexArray(v, vsize), indexVect);
    return r;
}