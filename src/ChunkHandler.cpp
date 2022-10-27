#include "ChunkHandler.h"
#include "Game.h"

ChunkHandler::ChunkHandler(){

}

void ChunkHandler::addChunk(Chunk* chunk){
    chunks.push_back(chunk);
}

// void EntityHandler::removeEntity(Entity* entity){
//     entities.remove(entities.begin(), entities.end(), entity);
// }

void ChunkHandler::tick(float fElapsedTime){
    for(auto chunk : chunks){
        chunk->tick(fElapsedTime);
    }
}

void ChunkHandler::render(Game* game){
    for(auto chunk : chunks){
        chunk->render(game);
    }
}