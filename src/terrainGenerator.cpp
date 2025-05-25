#include "terrainGenerator.h"
#include "vertex.h"
#include "Kamera.h"
#include "helper/tsqueue.h"
#include <memory>
#include <thread>

#define STB_PERLIN_IMPLEMENTATION
#include <stb/stb_perlin.h>

float perlinChunkHeight(float x, float y) {
    float h = 0;
    h += stb_perlin_turbulence_noise3(x/10, y/10, 0.1f, 1.3f, 0.1f, 6);
    return h;
}

std::pair< std::vector<Vertex>, std::vector<GLuint>> generateChunkMesh(int chunkX, int chunkY, int LOD) {
    assert((TERRAINGENERATOR_CHUNK_DETAIL % LOD) == 0);
    GLuint vert_per_chunk = (TERRAINGENERATOR_CHUNK_DETAIL / LOD);
    GLuint vpc_half = vert_per_chunk/2;
    std::vector<Vertex> vertices;
    for(GLuint i = 0; i < vert_per_chunk; i++) {
        for(GLuint j = 0; j < vert_per_chunk; j++) {
            Vertex v;
            float cX = (i / static_cast<float>(vert_per_chunk - 1) + (chunkX)) * TERRAINGENERATOR_CHUNK_SIZE;
            float cY = (j / static_cast<float>(vert_per_chunk - 1) + (chunkY)) * TERRAINGENERATOR_CHUNK_SIZE;
            
            glm::vec3 vector{
                static_cast<float>(cX),
                perlinChunkHeight(cX, cY),
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
    std::vector<GLuint> indices;

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
    return std::make_pair(vertices, indices);
}

void processTerrainQueue()
{
    while (!terrainGenQueue.empty()) {
        try {
            auto task = terrainGenQueue.pop();
            task();
        } catch (...) {
            printf("Error processing terrain generator queue!\n");
        }
    }
}


TerrainGenerator::TerrainGenerator(Camera& cam) : associated_cam(cam) {
    //std::thread generatorThread(&TerrainGenerator::updateTerrain, this);
    std::thread generatorThread([this] {
        while (true) {
            updateTerrain();
        }
        });
    generatorThread.detach();
}



void TerrainGenerator::updateTerrain() {
    glm::vec3 P;
    std::unique_lock<std::mutex> lock(associated_cam._mutex);
    P = associated_cam.Position;
    lock.unlock();
    int x = P.x / TERRAINGENERATOR_CHUNK_SIZE;
    int y = P.z / TERRAINGENERATOR_CHUNK_SIZE;

    for(int i = x - RENDER_DISTANCE; i < x + RENDER_DISTANCE; i++) {
        for(int j = y-RENDER_DISTANCE; j < y + RENDER_DISTANCE; j++) {
            if (chunkExists({i,j,1})) {
                continue;
            }
            printf("Generating chunk %i, %i at LOD %i\n", i, j, 1);
            chData data{ i, j, 1 };
            int LOD = std::pow(2, abs(i+j) % 3);
            auto VIPair = generateChunkMesh(i, j, 1);
            auto V = VIPair.first;
            auto I = VIPair.second;
            terrainGenQueue.push([this, data, V, I] {
                std::unique_lock<std::mutex> lock(_mutex);
                TerrainChunks.push_back(std::make_unique<Chunk>(data, V, I));
                });
        }
    }
}

bool TerrainGenerator::chunkExists(chData who)
{
    std::unique_lock<std::mutex> lock(_mutex);
    for (auto& pChunk : TerrainChunks) {
        try {
            auto& data = pChunk->data;
            if (data.x == who.x && data.y == who.y && data.LOD == who.LOD)
                return true;
        }
        catch (...) {
            // something went wrong, pretend it exists just in case
            return true;
        }
    }
    return false;
}

void TerrainGenerator::Draw(Shader& shader) {
    std::unique_lock<std::mutex> lock(_mutex);
    for(const auto& c : TerrainChunks) {
        c->terrainMesh.Draw(shader);
    }
}