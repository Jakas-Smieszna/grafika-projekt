#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H
#include <vector>
#include <string>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Tekstury.h"
#include "assimp/material.h"
#include "mesh.h"
#include "shader.h"

class Model {
public:
    Model(char *path) {
        loadModel(path);
    }
    void Draw(Shader &shader);
private:
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif // MODEL_CLASS_H