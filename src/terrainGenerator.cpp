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
#include <chrono>
void processTerrainQueue()
{
    auto t_start = std::chrono::steady_clock::now();
    while (!terrainGenQueue.empty()) {
        auto task = terrainGenQueue.pop();
        task();
        auto t_end = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double, std::milli>(t_end - t_start).count();
        if (elapsed > 1000) {
            printf("stopped processing due to surpassed time limit!\n");
            break;
        }
    }
}


TerrainGenerator::TerrainGenerator(Camera& cam) : associated_cam(cam), TerrainChunks(), lastCamChunk({21, 37, 0 }) {
    //std::thread generatorThread(&TerrainGenerator::updateTerrain, this);
    std::thread generatorThread([this] {
        while (true) {
            std::unique_lock<std::mutex> lock(associated_cam._mutex);
            glm::vec3 P = associated_cam.Position;
            lock.unlock();
            auto currCamChunk = getChunkPosFromCamPos(P);
            if (currCamChunk == lastCamChunk) continue;
            lastCamChunk = currCamChunk;
            updateTerrain(P);
        }
        });
    generatorThread.detach();
}

chData TerrainGenerator::getChunkPosFromCamPos(glm::vec3 P) {
    int x = P.x / TERRAINGENERATOR_CHUNK_SIZE;
    int y = P.z / TERRAINGENERATOR_CHUNK_SIZE;
    return { x, y, 0 };
}

void TerrainGenerator::updateTerrain(glm::vec3 P) {
    int x = P.x / TERRAINGENERATOR_CHUNK_SIZE;
    int y = P.z / TERRAINGENERATOR_CHUNK_SIZE;

    for(int i = x - RENDER_DISTANCE; i < x + RENDER_DISTANCE; i++) {
        for(int j = y-RENDER_DISTANCE; j < y + RENDER_DISTANCE; j++) {
            if (chunkExists({i,j,1})) {
                continue;
            }
            chData data{ i, j, 1 };
            int LOD = std::pow(2, abs(i+j) % 3);
            auto VIPair = generateChunkMesh(i, j, 1);
            auto V = VIPair.first;
            auto I = VIPair.second;
            terrainGenQueue.push([this, data, V, I] {
                std::unique_lock<std::mutex> lock(_mutex);
                //printf("adding chunk %i, %i\n", data.x, data.y);
                TerrainChunks.emplace(data, std::make_unique<Chunk>(data, V, I) );
                });
        }
    }
}

bool TerrainGenerator::chunkExists(chData who)
{
    std::unique_lock<std::mutex> lock(_mutex);
    return TerrainChunks.contains(who);
}

void TerrainGenerator::Draw(Shader& shader) {
    glm::vec3 P;
    std::unique_lock<std::mutex> camLock(associated_cam._mutex);
    P = associated_cam.Position;
    camLock.unlock();
    int x = P.x / TERRAINGENERATOR_CHUNK_SIZE;
    int y = P.z / TERRAINGENERATOR_CHUNK_SIZE;
    for (int i = x - RENDER_DISTANCE; i < x + RENDER_DISTANCE; i++) {
        for (int j = y - RENDER_DISTANCE; j < y + RENDER_DISTANCE; j++) {
            if (!chunkExists({ i,j,1 })) {
                continue;
            }
            std::unique_lock<std::mutex> ourLock(_mutex);
            TerrainChunks.at({ i, j, 1 })->terrainMesh.Draw(shader);
            ourLock.unlock();
        }
    }

}