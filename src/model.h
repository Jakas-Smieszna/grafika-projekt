#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H
#include <memory>
#include <vector>
#include <string>

#include "tinyobj/tiny_obj_loader.h"
#include "mesh.h"
#include "shader.h"

std::string getModelPath(std::string);

class Model {
public:
    Model(std::string path) {
        loadModel(getModelPath(path));
    }
    void Draw(Shader &shader);
private:
    std::unique_ptr<Mesh> modelMesh;
    std::string directory;

    void loadModel(std::string path);
    //std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#ifdef _WIN32
#define MODEL_RELPATH "resources\\"
#elif __linux__

#ifdef DEBUG_BUILD
#define MODEL_RELPATH "out/build/linux-debug-x64/bin/resources/"
#else
#define MODEL_RELPATH "out/build/linux-release-x64/bin/resources/"
#endif // DEBUG_BUILD

#else
#define MODEL_RELPATH ""
#endif // _WIN32

#endif // MODEL_CLASS_H