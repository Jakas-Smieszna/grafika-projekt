#include "terrainGenerator.h"
#include "vertex.h"

#define STB_PERLIN_IMPLEMENTATION
#include <stb/stb_perlin.h>

Mesh Chunk::generateChunkMesh(int LOD, int chunkX, int chunkY) {
    assert((TERRAINGENERATOR_CHUNK_SIZE % LOD) == 0);
    uint vert_per_chunk = (TERRAINGENERATOR_CHUNK_SIZE / LOD);
    std::vector<Vertex> vertices;
    for(uint i = 0; i < vert_per_chunk; i++) {
        for(uint j = 0; j < vert_per_chunk; j++) {
            Vertex v;
            int cX = i + chunkX*TERRAINGENERATOR_CHUNK_SIZE;
            int cY = j + chunkY*TERRAINGENERATOR_CHUNK_SIZE;
            glm::vec3 vector{
                static_cast<float>(cX),
                static_cast<float>(cY),
                stb_perlin_noise3(cX, cY, 0,
                     0, 0, 0)
            };
            v.Position = vector;
            v.Color = {0.7, 0.1, 0.1};
            
            // no troche nie ale niech bedzie
            v.Normal = glm::vec3{0.f, 0.f, 1.f};
            v.TexCoords = {0.f, 0.f};
            vertices.push_back(v);
        }
    }
    std::vector<uint> indices;
    for(uint i = 0; i < vert_per_chunk; i+=2) {
        for(uint j = 0; j < vert_per_chunk; j+=2) {
            indices.push_back(i*vert_per_chunk+j);
            indices.push_back(i*vert_per_chunk+j+1);
            indices.push_back((i+1)*vert_per_chunk+j);

            indices.push_back(i*vert_per_chunk+j+1);
            indices.push_back((i+1)*vert_per_chunk+j);
            indices.push_back((i+1)*vert_per_chunk+j+1);
        }
    }
    return Mesh(vertices, indices);
}

TerrainGenerator::TerrainGenerator() {
    updateTerrain();
}

void TerrainGenerator::updateTerrain() {
    for(int i = -2; i < 3; i++) {
        for(int j = -2; j < 3; j++) {
            TerrainChunks.push_back(Chunk(i,j));
        }
    }
}

void TerrainGenerator::Draw(Shader& shader) {
    for(Chunk c : TerrainChunks) {
        c.terrainMesh.Draw(shader);
    }
}