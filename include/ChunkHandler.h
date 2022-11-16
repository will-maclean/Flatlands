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
        return mChunks;
    }
private:
    std::vector<Chunk *> mChunks;

    Chunk* mLeftMostChunk;
    Chunk* mRightMostChunk;

    float mCreateNewChunkDistance;

    void checkCreateNewChunks(Game* game);
};