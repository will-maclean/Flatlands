#include "ChunkHandler.h"
#include "Game.h"
#include <iostream>

ChunkHandler::ChunkHandler(float createNewChunkDistance){
    this->mCreateNewChunkDistance = createNewChunkDistance;
    mLeftMostChunk = nullptr;
    mRightMostChunk = nullptr;
}

void ChunkHandler::addChunk(Chunk* chunk){
    mChunks.push_back(chunk);

    if(mLeftMostChunk == nullptr){
        std::cout << "setting leftmostchunk" << std::endl;
        mLeftMostChunk = chunk;
    }

    if(mRightMostChunk == nullptr){
        std::cout << "setting rightmostchunk" << std::endl;
        mRightMostChunk = chunk;
    }
}

// void EntityHandler::removeEntity(Entity* entity){
//     mEntities.remove(mEntities.begin(), mEntities.end(), entity);
// }

void ChunkHandler::tick(Game* game, float fElapsedTime){
    checkCreateNewChunks(game);

    for(auto chunk : mChunks){
        chunk->tick(fElapsedTime);
    }
}

void ChunkHandler::render(Game* game){
    for(auto chunk : mChunks){
        chunk->render(game);
    }
}

void ChunkHandler::checkCreateNewChunks(Game* game){
    if(mLeftMostChunk != nullptr){
        // check if the left-most chunk is currently close enought to the left edge of the screen
        if(game->getCentrePos().x - mLeftMostChunk->getAnchorLocation().x < mCreateNewChunkDistance){
            olc::vf2d newAnchorPos = {mLeftMostChunk->getAnchorLocation().x - 16 * 16, 0};

            auto* newChunk = new Chunk(newAnchorPos);
            addChunk(newChunk);

            mLeftMostChunk = newChunk;

            std::cout << "Creating new chunk to the left" << std::endl;
        }
    }

    if(mRightMostChunk != nullptr){
        // check if the right-most chunk is currently close enough to the right edge of the screen
        if(mRightMostChunk->getAnchorLocation().x + 16 * 16 - game->getGamePos().x < mCreateNewChunkDistance){
            olc::vf2d newAnchorPos = {mRightMostChunk->getAnchorLocation().x + 16 * 16, 0};

            auto* newChunk = new Chunk(newAnchorPos);
            addChunk(newChunk);

            mRightMostChunk = newChunk;

            std::cout << "Creating new chunk to the right" << std::endl;
        }
    }
}