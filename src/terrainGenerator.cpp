#include "terrainGenerator.h"
#include "vertex.h"
#include <memory>

#define STB_PERLIN_IMPLEMENTATION
#include <stb/stb_perlin.h>

float perlinChunkHeight(float x, float y) {
    float h = 0;
    h += stb_perlin_turbulence_noise3(x/10, y/10, 0.1f, 1.3f, 0.1f, 6);
    return h;
}

Mesh Chunk::generateChunkMesh(int LOD, int chunkX, int chunkY) {
    assert((TERRAINGENERATOR_CHUNK_SIZE % LOD) == 0);
    uint vert_per_chunk = (TERRAINGENERATOR_CHUNK_SIZE / LOD) + 2;
    uint vpc_half = vert_per_chunk/2;
    std::vector<Vertex> vertices;
    for(uint i = 0; i < vert_per_chunk; i++) {
        //const int cY = i * vert_per_chunk - vpc_half + TERRAINGENERATOR_CHUNK_SIZE*chunkX;
        for(uint j = 0; j < vert_per_chunk; j++) {
            Vertex v;
            //const int cX = j * vert_per_chunk - vpc_half + TERRAINGENERATOR_CHUNK_SIZE*chunkY;
            
            float cX = i/static_cast<float>(vert_per_chunk-1) + (chunkX);
            float cY = j/static_cast<float>(vert_per_chunk-1) + (chunkY);
            
            glm::vec3 vector{
                static_cast<float>(cX),
                perlinChunkHeight(cX, cY),
                //stb_perlin_noise3_seed(cX, cY, 0.52f, 32, 16, 0, 2137),
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

    for(int y = 0; y < vert_per_chunk-1; y++) {
        for(int x = 0; x < vert_per_chunk-1; x++) {
            const int a = x + vert_per_chunk * y;
            const int b = x + vert_per_chunk * (y+1);
            const int c = (x+1) + vert_per_chunk * (y+1);
            const int d = (x+1) + vert_per_chunk * y;
            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(d);
            indices.push_back(b);
            indices.push_back(c);
            indices.push_back(d);
        }
    }

    /*
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
    */
    return Mesh(vertices, indices);
}

TerrainGenerator::TerrainGenerator() {
    updateTerrain();
}

void TerrainGenerator::updateTerrain() {
    for(int i = -RENDER_DISTANCE; i < RENDER_DISTANCE; i++) {
        for(int j = -RENDER_DISTANCE; j < RENDER_DISTANCE; j++) {
            TerrainChunks.push_back(std::make_unique<Chunk>(i,j, 1));
        }
    }
}

void TerrainGenerator::Draw(Shader& shader) {
    for(const auto& c : TerrainChunks) {
        c->terrainMesh.Draw(shader);
    }
}