#include "mesh.h"
#include "shader.h"
#include "vertex.h"
#include <vector>

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

Mesh getTestMesh() {
    const GLfloat v[] = {
   -0.5f, 1.5f,  0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f,								0.0f, -1.0f, 0.0f,
   -0.5f, 1.5f, -0.5f,0.0f, 1.0f, 1.0f,0.0f, 3.0f,	0.0f,   -1.0f, 0.0f,
	0.5f, 1.5f, -0.5f,1.0f, 1.0f, 0.0f,3.0f, 3.0f,	0.0f,   -1.0f, 0.0f,
	0.5f, 1.5f,  0.5f,0.0f, 1.0f, 1.0f,3.0f, 0.0f,	0.0f,   -1.0f, 0.0f
    };

    std::vector<Vertex> vertexVect;
    
    for(int i = 0; i < 43; i+=11) {
        vertexVect.push_back(Vertex{
            glm::vec3{v[i], v[i+1], v[i+2]},
            glm::vec3{v[i+3], v[i+4], v[i+5]},
            glm::vec2{v[i+6], v[i+7]},
            glm::vec3{v[i+8], v[i+9], v[i+10]}
        });
    }
    std::vector<GLuint> indexVect = {
        0, 1, 3,
        1, 3, 2
    };
    Mesh r = Mesh(vertexVect, indexVect);
    return r;
}