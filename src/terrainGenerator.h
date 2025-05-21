#ifndef TERRAINGENERATOR_CLASS_H
#define TERRAINGENERATOR_CLASS_H

#include "mesh.h"
#include "shader.h"
#include <vector>

#ifndef TERRAINGENERATOR_CHUNK_SIZE
#define TERRAINGENERATOR_CHUNK_SIZE 4
#endif

struct ivec2 {
    int x;
    int y;
};

class Chunk {
public:
    ivec2 position;
    Mesh terrainMesh;
    Chunk(int cX, int cY, int LOD = 1) : terrainMesh(generateChunkMesh(LOD, cX, cY)) {};
private:
    Mesh generateChunkMesh(int LOD, int chunkX, int chunkY);
};

class TerrainGenerator {
public:
    TerrainGenerator();

    void Draw(Shader& shader);
    void updateTerrain();
private:
    std::vector<Chunk> TerrainChunks;
    
};

#endif // TERRAINGENERATOR_CLASS_H