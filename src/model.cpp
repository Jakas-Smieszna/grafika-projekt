#include "model.h"
#include "glm/fwd.hpp"
#include "vertex.h"
#include "helper/debugutils.h"

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void Model::Draw(Shader &shader) {
    for (Mesh m : meshes) {
        m.Draw(shader);
    }
}

void Model::loadModel(std::string path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        eprintf("[ASSIMP]: %s", importer.GetErrorString());
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for (uint i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for(uint i = 0; i < node->mNumMeshes; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    std::vector<Texture> textures;
    for(uint i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;
        // vertices
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        vertex.Color = glm::vec3{0, 0, 0};
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        //tex coords
        if(mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        } else {
            vertex.TexCoords = glm::vec2{0.f, 0.f};
        }
        vertices.push_back(vertex);
    }
    for(uint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(uint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    return Mesh(vertices, indices);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;
    for(uint i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture(str.C_Str(), GL_TEXTURE_2D, i, GL_RGB, GL_RGB);
        texture.type = typeName;
        textures.push_back(texture);
    }
    return textures;
}