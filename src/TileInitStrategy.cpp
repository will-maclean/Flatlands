#include "TileInitStrategy.h"
#include "Chunk.h"
#include "Tile.h"

#include <stdlib.h>

void fillAll(Chunk* chunk){
    for(int i = 0; i < chunk->getHeight(); i++){
        for(int j = 0; j < chunk->getWidth(); j++){
            chunk->setTile(new DirtTile(), j, i);
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

    for(int i = 0; i < chunk->getHeight(); i++){
        for(int j = 0; j < chunk->getWidth(); j++){
            if(i < threshold){
                // EmptyTile only
                chunk->setTile(new EmptyTile(), j, i);
                emptyMap[i][j] = true;
            }else{
                // 90% dirt, 10% chance empty
                int r = rand() % 100;
                if(r < 90){
                    if(i >=2 && emptyMap[i-1][j] && emptyMap[i-2][j]){
                        chunk->setTile(new GrassyDirtTile(), j, i);
                    }else{
                        chunk->setTile(new DirtTile(), j, i);
                    }
                    emptyMap[i][j] = false;
                }else{
                    chunk->setTile(new EmptyTile(), j, i);
                    emptyMap[i][j] = true;
                }
            }
        }
    }
}