#pragma once

#include <vector>
#include "Chunk.h"

class Game;

class ChunkHandler{
private:
    std::vector<Chunk *> chunks;

public:
    ChunkHandler();

    void addChunk(Chunk* entity);

    // void removeEntity(Entity* entity);

    void tick(float fElapsedTime);

    void render(Game* game);
};