#include "terrainGenerator.h"
#include "vertex.h"

#define STB_PERLIN_IMPLEMENTATION
#include <stb/stb_perlin.h>

#include <iostream>


Mesh Chunk::generateChunkMesh(int LOD, int chunkX, int chunkY) {
    assert((TERRAINGENERATOR_CHUNK_SIZE % LOD) == 0);
    uint vert_per_chunk = (TERRAINGENERATOR_CHUNK_SIZE / LOD) + 1;
    std::vector<Vertex> vertices;
    for(uint i = 0; i < vert_per_chunk; i++) {
        for(uint j = 0; j < vert_per_chunk; j++) {
            Vertex v;
            int cX = i + chunkX*TERRAINGENERATOR_CHUNK_SIZE;
            int cY = j + chunkY*TERRAINGENERATOR_CHUNK_SIZE;
            glm::vec3 vector{
                static_cast<float>(cX),
                stb_perlin_noise3(cX, cY, 0.1f,
                     0, 0, 0),
                static_cast<float>(cY)
            };
            v.Position = vector;
            v.Color = {0.7, vector.y, 0.1};
            
            // no troche nie ale n5iech bedzie
            v.Normal = glm::vec3{0.f, 0.f, 1.f};
            v.TexCoords = {0.f, 0.f};
            vertices.push_back(v);
        }
    }
    std::vector<uint> indices;
    for(uint i = 0; i < vert_per_chunk; i++) {
        for(uint j = 0; j < vert_per_chunk; j++) {
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
    Chunk t = Chunk(1, 3);
    for(int i = -2; i < 3; i++) {
        for(int j = -2; j < 3; j++) {
            Chunk freshGen = Chunk(i,j);
            TerrainChunks.push_back(freshGen);
        }
    }
}

void TerrainGenerator::Draw(Shader& shader) {
    for(Chunk c : TerrainChunks) {
        c.terrainMesh.Draw(shader);
    }
}