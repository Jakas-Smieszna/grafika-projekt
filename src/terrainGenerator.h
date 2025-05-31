#ifndef TERRAINGENERATOR_CLASS_H
#define TERRAINGENERATOR_CLASS_H

#include "mesh.h"
#include "shader.h"
#include "Kamera.h"
#include "StatusGry.h"
#include <memory>
#include <vector>
#include <utility>
#include <mutex>
#include <map>

//Rozmiar chunk-u jeżeli chodzi o "unity" openGL
// tutaj początek by był (0, 0) a koniec (32, 32)
#ifndef TERRAINGENERATOR_CHUNK_SIZE
#define TERRAINGENERATOR_CHUNK_SIZE 16
#endif

// ilość vertexów w boku; fajnie jak jest potęgą dwójki
#define TERRAINGENERATOR_CHUNK_DETAIL 16

#ifndef RENDER_DISTANCE
#define RENDER_DISTANCE 7
#endif

struct chData {
    int x;
    int y;
    int LOD;

    bool operator<(const chData& rhs) const {
        if (x < rhs.x) return true;
        if (x > rhs.x) return false;
        return (y < rhs.y);
    }
    bool operator==(const chData& rhs) const {
        return (x == rhs.x && y == rhs.y);
    }
};



class Chunk {
public:
    chData data;
    Mesh terrainMesh;
    // Chunk musi wygenerować własny mesh z verteksów i indeksów.
    // Zapobiega to problemów z pamięcią itp.
    Chunk(chData chnkData, std::vector<Vertex> V, std::vector<GLuint> I) : data(chnkData), terrainMesh(Mesh(V, I)) {};
};


std::pair< std::vector<Vertex>, std::vector<GLuint>> generateChunkMesh(int chunkX, int chunkY, int LOD);

class TerrainGenerator {
public:
    TerrainGenerator(Pakiet_Zmiennych& vars);
    ~TerrainGenerator() {
        //std::unique_lock<std::mutex> lock(assoc_vars._mutex);
        TerrainChunks.clear();
    }

    chData getChunkPosFromCamPos(glm::vec3 P);


    void Draw(Shader& shader);
    void updateTerrain(glm::vec3 P);
private:
    bool chunkExists(chData who);
    void dropChunk(chData who);

    chData lastCamChunk;

    // trochę takie długie, ale musimy uniknąć
    // kopiowania mesh-y, bo inaczej wywołuje się
    // ich dekonstruktor, który niszczy ebo, vbo, vao
    //std::vector<std::unique_ptr<Chunk>> TerrainChunks;
    std::map<chData, std::unique_ptr<Chunk>> TerrainChunks;

    // Mutex raczej nie powinien być potrzebny, bo
    // wszystko (rysowanie + dodawanie do TerrainChunks)
    // powinno wykonywać się na tym samym wątku.
    std::mutex _mutex;
    Pakiet_Zmiennych& assoc_vars;
    
};

void processTerrainQueue();

#endif // TERRAINGENERATOR_CLASS_H