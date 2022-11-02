#include "ChunkHandler.h"
#include "Game.h"
#include <iostream>

ChunkHandler::ChunkHandler(float createNewChunkDistance){
    this->createNewChunkDistance = createNewChunkDistance;
    leftMostChunk = nullptr;
    rightMostChunk = nullptr;
}

void ChunkHandler::addChunk(Chunk* chunk){
    chunks.push_back(chunk);

    if(leftMostChunk == nullptr){
        std::cout << "setting leftmostchunk" << std::endl;
        leftMostChunk = chunk;
    }

    if(rightMostChunk == nullptr){
        std::cout << "setting rightmostchunk" << std::endl;
        rightMostChunk = chunk;
    }
}

// void EntityHandler::removeEntity(Entity* entity){
//     entities.remove(entities.begin(), entities.end(), entity);
// }

void ChunkHandler::tick(Game* game, float fElapsedTime){
    checkCreateNewChunks(game);

    for(auto chunk : chunks){
        chunk->tick(fElapsedTime);
    }
}

void ChunkHandler::render(Game* game){
    for(auto chunk : chunks){
        chunk->render(game);
    }
}

void ChunkHandler::checkCreateNewChunks(Game* game){
    if(leftMostChunk != nullptr){
        // check if the left-most chunk is currently close enought to the left edge of the screen
        if(game->getCentrePos().x - leftMostChunk->getAnchorLocation().x < createNewChunkDistance){
            olc::vf2d newAnchorPos = {leftMostChunk->getAnchorLocation().x - 16 * 16, 0};

            auto* newChunk = new Chunk(newAnchorPos);
            addChunk(newChunk);

            leftMostChunk = newChunk;

            std::cout << "Creating new chunk to the left" << std::endl;
        }
    }

    if(rightMostChunk != nullptr){
        // check if the right-most chunk is currently close enough to the right edge of the screen
        if(rightMostChunk->getAnchorLocation().x + 16 * 16 - game->getGamePos().x < createNewChunkDistance){
            olc::vf2d newAnchorPos = {rightMostChunk->getAnchorLocation().x + 16 * 16, 0};

            auto* newChunk = new Chunk(newAnchorPos);
            addChunk(newChunk);

            rightMostChunk = newChunk;

            std::cout << "Creating new chunk to the right" << std::endl;
        }
    }
}