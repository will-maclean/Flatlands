#include "TileInitStrategy.h"
#include "Chunk.h"
#include "Tile.h"
#include "olcPixelGameEngine.h"
#include <stdlib.h>

void fillAll(Chunk* chunk){
    olc::vf2d chunkAnchorLocation = chunk->getAnchorLocation();

    for(int i = 0; i < chunk->getHeight(); i++){
        for(int j = 0; j < chunk->getWidth(); j++){
            olc::vf2d anchorLocation = {chunkAnchorLocation.x + j * chunk->getTileWidth(), chunkAnchorLocation.y + i * chunk->getTileHeight()};
            chunk->setTile(new DirtTile(anchorLocation), j, i);
        }
    }
}

void defaultTileInitStrategy(Chunk* chunk){
    // fillAll(chunk);  // useful for debugging
    // defaults strategy:
    //
    // top 10% of chunk -> EmptyTile
    // lower 75% of chunk -> 90% DirtBlock, 10% EmptyTile
    
    int threshold = chunk->getHeight() * 0.1;

    bool emptyMap[chunk->getHeight()][chunk->getWidth()];

    olc::vf2d chunkAnchorLocation = chunk->getAnchorLocation();

    for(int i = 0; i < chunk->getHeight(); i++){
        for(int j = 0; j < chunk->getWidth(); j++){
            olc::vf2d anchorLocation = {chunkAnchorLocation.x + j * chunk->getTileWidth(), chunkAnchorLocation.y + i * chunk->getTileHeight()};
            if(i < threshold){
                // EmptyTile only
                chunk->setTile(new EmptyTile(anchorLocation), j, i);
                emptyMap[i][j] = true;
            }else{
                // 90% dirt, 10% chance empty
                int r = rand() % 100;
                if(r < 85){
                    if(i >=2 && emptyMap[i-1][j] && emptyMap[i-2][j]){
                        chunk->setTile(new GrassyDirtTile(anchorLocation), j, i);
                    }else{
                        chunk->setTile(new DirtTile(anchorLocation), j, i);
                    }
                    emptyMap[i][j] = false;
                }else{
                    chunk->setTile(new EmptyTile(anchorLocation), j, i);
                    emptyMap[i][j] = true;
                }
            }
        }
    }
}
