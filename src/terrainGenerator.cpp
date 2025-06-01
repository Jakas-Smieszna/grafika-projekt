#include "terrainGenerator.h"
#include "Tekstury.h"
#include "vertex.h"
#include "Kamera.h"
#include "helper/tsqueue.h"
#include "helper/debugutils.h"
#include <memory>
#include <thread>
#include <chrono>
#include <cmath>

#define STB_PERLIN_IMPLEMENTATION
#include <stb/stb_perlin.h>

float perlinChunkHeight(float x, float y) {
    float h = -5.f;
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
            float cX = (i / static_cast<float>(vert_per_chunk - 1) ) * TERRAINGENERATOR_CHUNK_SIZE;
            float cY = (j / static_cast<float>(vert_per_chunk - 1) ) * TERRAINGENERATOR_CHUNK_SIZE;
            float genOffsetX = chunkX * TERRAINGENERATOR_CHUNK_SIZE;
            float genOffsetY = chunkY * TERRAINGENERATOR_CHUNK_SIZE;
            glm::vec3 vector{
                static_cast<float>(cX),
                perlinChunkHeight(cX + genOffsetX, cY + genOffsetY),
                static_cast<float>(cY)
            };
            v.Position = vector;
            v.Color = {0.7, vector.y, 0.1};
            // no troche nie ale n5iech bedzie
            v.Normal = glm::vec3{0.f, 1.f, 0.f};
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
            for(auto k : {a, b, d, b, c, d}) {
                indices.push_back(k);
            }
        }
    }
    
    return std::make_pair(vertices, indices);
}
void processTerrainQueue()
{
    auto t_start = std::chrono::steady_clock::now();
    while (!terrainGenQueue.empty()) {
        auto task = terrainGenQueue.pop();
        task();
        auto t_end = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double, std::milli>(t_end - t_start).count();
        if (elapsed > 1000) {
            dbgprintf("stopped processing due to surpassed time limit!\n");
            break;
        }
    }
}

TerrainGenerator::TerrainGenerator(Pakiet_Zmiennych& vars) : assoc_vars(vars), TerrainChunks(), lastCamChunk({21, 37, 0}) {
    //std::thread generatorThread(&TerrainGenerator::updateTerrain, this);
    obstacleModels.emplace_back(Model("rock.obj"));
    obstacleModels.emplace_back(Model("tree.obj"));
    std::thread generatorThread([this] {
        while (true) {
            //std::unique_lock<std::mutex> lock(associated_cam._mutex);
            glm::vec3 P = assoc_vars.Biezaca_pozycja;
            //lock.unlock();
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

#define RANDLFLOAT (static_cast<double>(rand()) / RAND_MAX)
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
                TerrainChunks.emplace(data, std::make_unique<Chunk>(data, V, I) );
            });
            if(std::abs(i) > 1 && std::abs(j) > 1 && (RANDLFLOAT < OBSTRUCTION_SPAWN_CHANCE)) {
                terrainGenQueue.push([this, data] {
                    float cX = (RANDLFLOAT) * TERRAINGENERATOR_CHUNK_SIZE;
                    float cY = (RANDLFLOAT) * TERRAINGENERATOR_CHUNK_SIZE;
                    float genOffsetX = data.x * TERRAINGENERATOR_CHUNK_SIZE;
                    float genOffsetY = data.y * TERRAINGENERATOR_CHUNK_SIZE;
                    float type = (RANDLFLOAT < 0.5 ? 0 : 1);
                    std::unique_lock<std::mutex> lock(_mutex);
                    TerrainChunks.at(data)->obstacleModels.emplace_back(
                        std::make_pair(
                            // place in the world
                            glm::vec4(
                                static_cast<float>(cX),
                                perlinChunkHeight(cX + genOffsetX, cY + genOffsetY) + 2.f,
                                static_cast<float>(cY),
                                type // determines if tree or rock
                            ), 
                            // unused rotation vector
                            glm::vec3(
                                glm::radians(RANDLFLOAT * 360),
                                glm::radians(RANDLFLOAT * 360),
                                glm::radians(RANDLFLOAT * 360)
                            )
                        )
                    );
                });
            }
        }
    }
}
#define COLLISION_CHECK_CHUNK_RADIUS 2
bool TerrainGenerator::checkObstacleCollisions() {
    glm::vec3 P;
    P = assoc_vars.Biezaca_pozycja;
    int x = P.x / TERRAINGENERATOR_CHUNK_SIZE;
    int y = P.z / TERRAINGENERATOR_CHUNK_SIZE;
    for (int i = x - COLLISION_CHECK_CHUNK_RADIUS; i < x + COLLISION_CHECK_CHUNK_RADIUS; i++) {
        for (int j = y - COLLISION_CHECK_CHUNK_RADIUS; j < y + COLLISION_CHECK_CHUNK_RADIUS; j++) {
            if (!chunkExists({ i,j,1 })) {
                continue;
            }
            auto& chunk = TerrainChunks.at({i,j,1});
            if(chunk->obstacleModels.size() == 0) {
                continue;
            }

            for(auto obstacle : chunk->obstacleModels) {
                glm::vec3 chnkPosVec = glm::vec3(
                    i*TERRAINGENERATOR_CHUNK_SIZE,
                    0, j * TERRAINGENERATOR_CHUNK_SIZE
                );
                auto obstPos = (chnkPosVec + glm::vec3(obstacle.first));
                float dist = std::abs(glm::length(obstPos - assoc_vars.Biezaca_pozycja));
                if(dist < OBSTRUCTION_COLLISION_DISTANCE) {
                    return true;
                }
            }
        }
    }
    return false;
    
}
#undef RANDLFLOAT
bool TerrainGenerator::chunkExists(chData who)
{
    std::unique_lock<std::mutex> lock(_mutex);
    return TerrainChunks.contains(who);
}

void TerrainGenerator::Draw(Shader& shader, Shader& obstacleShader) {
    glm::vec3 P;
    //std::unique_lock<std::mutex> camLock(associated_cam._mutex);
    P = assoc_vars.Biezaca_pozycja;
    //camLock.unlock();

    int x = P.x / TERRAINGENERATOR_CHUNK_SIZE;
    int y = P.z / TERRAINGENERATOR_CHUNK_SIZE;
    for (int i = x - RENDER_DISTANCE; i < x + RENDER_DISTANCE; i++) {
        for (int j = y - RENDER_DISTANCE; j < y + RENDER_DISTANCE; j++) {
            if (!chunkExists({ i,j,1 })) {
                continue;
            }
            glm::mat4 chunkModel = glm::mat4(1.0f);
            glm::vec3 chnkPosVec = glm::vec3(
                    -P.x + i*TERRAINGENERATOR_CHUNK_SIZE,
                    0, -P.z + j * TERRAINGENERATOR_CHUNK_SIZE
                );
            chunkModel = glm::translate(chunkModel, chnkPosVec);
            shader.Activate();
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(chunkModel));
            std::unique_lock<std::mutex> ourLock(_mutex);
            auto &ourChnk = TerrainChunks.at({ i, j, 1 });
            ourChnk->terrainMesh.Draw(shader); // draw chunk proper
            for(auto pair : ourChnk->obstacleModels) {
                glm::vec4 pos = pair.first;
                glm::vec3 rot = pair.second;
                glm::mat4 obstModel = glm::translate(glm::mat4(1.0f), chnkPosVec);
                obstModel = glm::translate(chunkModel, glm::vec3(pos));
                // use W coord to determine the model -- todo
                obstacleShader.Activate();
			    glUniformMatrix4fv(glGetUniformLocation(obstacleShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(obstModel));
                obstacleModels[static_cast<int>(pos.w)].Draw(obstacleShader);
            }
            ourLock.unlock();
        }
    }

}