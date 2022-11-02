#pragma once

#include <vector>
#include "Chunk.h"

class Game;

class ChunkHandler{
public:
    ChunkHandler(float createNewChunkDistance);

    void addChunk(Chunk* entity);

    // void removeEntity(Entity* entity);

    void tick(Game* game, float fElapsedTime);

    void render(Game* game);

    std::vector<Chunk *> getChunks(){
        return chunks;
    }
private:
    std::vector<Chunk *> chunks;

    Chunk* leftMostChunk;
    Chunk* rightMostChunk;

    float createNewChunkDistance;

    void checkCreateNewChunks(Game* game);
};