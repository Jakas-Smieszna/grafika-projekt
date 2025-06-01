#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H
#include <memory>
#include <vector>
#include <string>


#include <tol/tiny_obj_loader.h>

#include "Tekstury.h"
#include "mesh.h"
#include "shader.h"

std::string getModelPath(std::string);

class Model {
public:
    Model(std::string obj) : modelTextures() {
        loadModel(getModelPath(obj));
    }
    void Draw(Shader &shader) {
        int i = 0;
        shader.Activate();
        for(const auto &T : modelTextures) {
            T->texUnit(shader, ("texture" + std::to_string(i)).c_str(), i++);
            T->Bind();
        }
        modelMesh->Draw(shader);
    }
private:
    std::unique_ptr<Mesh> modelMesh;

    std::vector<std::unique_ptr<Texture>> modelTextures;

    void loadModel(std::string objPath);
    void processMaterials(const std::vector<tinyobj::material_t> &materials);
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