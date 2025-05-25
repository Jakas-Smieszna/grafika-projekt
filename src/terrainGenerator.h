#ifndef TERRAINGENERATOR_CLASS_H
#define TERRAINGENERATOR_CLASS_H

#include "mesh.h"
#include "shader.h"
#include <memory>
#include <vector>
#include <utility>
#include <mutex>

#ifndef TERRAINGENERATOR_CHUNK_SIZE
#define TERRAINGENERATOR_CHUNK_SIZE 32
#endif
#ifndef RENDER_DISTANCE
#define RENDER_DISTANCE 64
#endif

struct chData {
    int x;
    int y;
    int LOD;
};

class Chunk {
public:
    chData data;
    Mesh terrainMesh;
    // Chunk musi wygenerować własny mesh z verteksów i indeksów.
    // Zapobiega to problemów z pamięcią itp.
    Chunk(chData chnkData, std::vector<Vertex> V, std::vector<GLuint> I) : data(chnkData), terrainMesh(Mesh(V, I)) {};
private:
};

std::pair< std::vector<Vertex>, std::vector<GLuint>> generateChunkMesh(int chunkX, int chunkY, int LOD);

class TerrainGenerator {
public:
    TerrainGenerator();

    void Draw(Shader& shader);
    void updateTerrain();
private:
    // trochę takie długie, ale musimy uniknąć
    // kopiowania mesh-y, bo inaczej wywołuje się
    // ich dekonstruktor, który niszczy ebo, vbo, vao
    std::vector<std::unique_ptr<Chunk>> TerrainChunks;
    // Mutex raczej nie powinien być potrzebny, bo
    // wszystko (rysowanie + dodawanie do TerrainChunks)
    // powinno wykonywać się na tym samym wątku.
    std::mutex _mutex;
    
};

void processTerrainQueue();

#endif // TERRAINGENERATOR_CLASS_H