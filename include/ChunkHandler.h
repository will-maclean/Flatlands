#pragma once

#include <vector>
#include "Chunk.h"

class Game;

class ChunkHandler{
public:
    ChunkHandler();

    void addChunk(Chunk* entity);

    // void removeEntity(Entity* entity);

    void tick(float fElapsedTime);

    void render(Game* game);

    std::vector<Chunk *> getChunks(){
        return chunks;
    }
private:
    std::vector<Chunk *> chunks;

};