#include "Chunk.h"
#include "TileInitStrategy.h"
#include "Game.h"

Chunk::Chunk(olc::vi2d anchorLocation){
    this->anchorLocation = anchorLocation;

    // init the tiles
    defaultTileInitStrategy(this);
}

void Chunk::tick(float fElapsedTime){
    // tick all the tiles
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            tileArr[i][j]->tick(fElapsedTime);
        }
    }
}

void Chunk::render(Game* game){
    // tick all the tiles
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            tileArr[i][j]->render(game, {anchorLocation.x + j * tileRenderWidth, anchorLocation.y + i * tileRenderHeight});
        }
    }
}