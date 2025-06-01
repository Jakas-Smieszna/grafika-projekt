#include "model.h"
#include "vertex.h"
#include "mesh.h"
#include "helper/debugutils.h"
#include <memory>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tol/tiny_obj_loader.h>

std::string getModelPath(std::string who) {
    return std::string{MODEL_RELPATH} + who;
}

void Model::Draw(Shader &shader) {
    modelMesh->Draw(shader);
}

void Model::loadModel(std::string path) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str())) {
        eprintf("FAILED TO LOAD OBJ %s\n", path.c_str());
        return;
    }


    std::vector<Vertex> V;
    std::vector<GLuint> I;

    for (const auto& shape : shapes) {
        for(const auto& index : shape.mesh.indices) {
            Vertex v{};

            v.Position = {
                attrib.vertices[3*index.vertex_index + 0],
                attrib.vertices[3*index.vertex_index + 1],
                attrib.vertices[3*index.vertex_index + 2]
            };

            v.Normal = {
                attrib.normals[3*index.normal_index + 0],
                attrib.normals[3*index.normal_index + 1],
                attrib.normals[3*index.normal_index + 2]
            };

            v.TexCoords = {
                attrib.texcoords[2*index.texcoord_index + 0],
                attrib.texcoords[2*index.texcoord_index + 1]
            };

            V.push_back(v);
            I.push_back(I.size());
        }
    }
    modelMesh = std::make_unique<Mesh>(V, I);
}

/*
std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;
    for(GLuint i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture(str.C_Str(), GL_TEXTURE_2D, i, GL_RGB, GL_RGB);
        texture.type = typeName;
        textures.push_back(texture);
    }
    return textures;
}
*/